/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_wires.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:32:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/17 01:43:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	slope(int n0, int n1)
{
	if (n0 < n1)
		return (1);
	return (-1);
}

// line drawing algorithm
// version of Bresenham's algorithm, as found in
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
static void	bresenham(t_data_fdf *data, t_point *a, t_point *b, t_fcol fcol)
{
	const t_point	a0 = *a;
	const int		d[2] = {ft_abs(b->c.x - a->c.x), -ft_abs(b->c.y - a->c.y)};
	const int		s[2] = {slope(a->c.x, b->c.x), slope(a->c.y, b->c.y)};
	int				error[2];

	error[0] = d[0] + d[1];
	while (fdf_pixel(data->mlx_ptr, data->img, (int [2]){a->c.x, a->c.y},
		fcol(&a0, a, b)) && (a->c.x != b->c.x || a->c.y != b->c.y))
	{
		error[1] = error[0] << 1;
		if (error[1] >= d[1])
		{
			if (a->c.x == b->c.x)
				break ;
			error[0] += d[1];
			a->c.x += s[0];
		}
		if (error[1] <= d[0])
		{
			if (a->c.y == b->c.y)
				break ;
			error[0] += d[0];
			a->c.y += s[1];
		}
	}
}

static void	check_wire(t_data_fdf *data, t_point *a, t_point *b, t_fcol fcol)
{
	const int	cp[4] = {cross_prod_sign(a->c.x, a->c.y, b->c.x, b->c.y),
		cross_prod_sign(a->c.x - PIX_X + 1, a->c.y, b->c.x - PIX_X + 1, b->c.y),
		cross_prod_sign(a->c.x, a->c.y - PIX_Y + 1, b->c.x, b->c.y - PIX_Y + 1),
		cross_prod_sign(a->c.x - PIX_X + 1, a->c.y - PIX_Y + 1,
			b->c.x - PIX_X + 1, b->c.y - PIX_Y + 1)};

	if ((0 <= a->c.x && a->c.x < PIX_X && 0 <= a->c.y && a->c.y < PIX_Y)
		|| (0 <= b->c.x && b->c.x < PIX_X && 0 <= b->c.y && b->c.y < PIX_Y)
		|| cp[0] * cp[1] <= 0 || cp[0] * cp[2] <= 0 || cp[1] * cp[3] <= 0
		|| cp[2] * cp[3] <= 0)
		bresenham(data, a, b, fcol);
}

static t_point	*transform(t_map_fdf *map, t_point *dst, const t_point *src)
{
	int		zoom;

	dst->color_trgb = src->color_trgb;
	dst->c.x = src->c.x - map->view.x;
	dst->c.y = src->c.y - map->view.y;
	zoom = map->steps_zoom;
	while (zoom > 0)
	{
		dst->c.x = dst->c.x * ZR1 / ZR2;
		dst->c.y = dst->c.y * ZR1 / ZR2;
		zoom--;
	}
	while (zoom < 0)
	{
		dst->c.x = dst->c.x * ZR2 / ZR1;
		dst->c.y = dst->c.y * ZR2 / ZR1;
		zoom++;
	}
	dst->c.x = dst->c.x * map->zoom_fit[0] / map->zoom_fit[1] + ICEN_X;
	dst->c.y = dst->c.y * map->zoom_fit[0] / map->zoom_fit[1] + ICEN_Y;
	return (dst);
}

void	plot_wires(t_data_fdf *dt)
{
	size_t	rc[2];
	t_point	dst[2];
	t_fcol	fcol;

	fcol = pixel_color_smp;
	if (dt->map->flags & CGRAD)
		fcol = pixel_color_grd;
	t_point (*const src)[dt->map->cols] = (void *)dt->map->points;
	rc[0] = 0;
	while (++rc[0] < dt->map->rows)
	{
		rc[1] = dt->map->cols;
		while (rc[1]--)
			check_wire(dt, transform(dt->map, dst, &src[rc[0] - 1][rc[1]]),
				transform(dt->map, dst + 1, &src[rc[0]][rc[1]]), fcol);
	}
	rc[1] = 0;
	while (++rc[1] < dt->map->cols)
	{
		rc[0] = dt->map->rows;
		while (rc[0]--)
			check_wire(dt, transform(dt->map, dst, &src[rc[0]][rc[1] - 1]),
				transform(dt->map, dst + 1, &src[rc[0]][rc[1]]), fcol);
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img->img_ptr, 0, 0);
}
