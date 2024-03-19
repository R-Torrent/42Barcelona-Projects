/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_wires.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:32:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/19 16:16:12 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	put_pixel(void *mlx_ptr, struct s_img *img, int *x,
	unsigned int color_trgb)
{
	char		*pixel;
	const int	bytes_per_pixel = img->bits_per_pixel / CHAR_BIT;

	if (x[0] >= 0 && x[0] < PIX_X && x[1] >= 0 && x[1] < PIX_Y)
	{
		pixel = img->addr + (x[0] * img->size_line + x[1] * bytes_per_pixel);
		*(unsigned int *)pixel = mlx_get_color_value(mlx_ptr, color_trgb);
	}
	return (color_trgb);
}

// line drawing algorithm
// version of Bresenham's algorithm, as found in
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
static void	bresenham(t_data_fdf *dt, t_point *a, t_point *b, t_fcol fcol)
{
	const t_point	a0 = *a;
	const int		d[2] = {ft_abs(b->c.x - a->c.x), -ft_abs(b->c.y - a->c.y)};
	const int		s[2] = {slope(a->c.x, b->c.x), slope(a->c.y, b->c.y)};
	int				error[2];

	error[0] = d[0] + d[1];
	while (put_pixel(dt->mlx_ptr, dt->img + dt->img_buffer, (int [2]){a->c.x,
			a->c.y}, fcol(&a0, a, b)) && (a->c.x != b->c.x || a->c.y != b->c.y))
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

static void	wire_visibility(t_data_fdf *dt, t_point *a, t_point *b)
{
	t_fcol		fcol;
	const int	cp[4] = {cross_prod_sign(a->c.x, a->c.y, b->c.x, b->c.y),
		cross_prod_sign(a->c.x - PIX_X + 1, a->c.y, b->c.x - PIX_X + 1, b->c.y),
		cross_prod_sign(a->c.x, a->c.y - PIX_Y + 1, b->c.x, b->c.y - PIX_Y + 1),
		cross_prod_sign(a->c.x - PIX_X + 1, a->c.y - PIX_Y + 1,
			b->c.x - PIX_X + 1, b->c.y - PIX_Y + 1)};

	fcol = pixel_color_smp;
	if (dt->map->flags & CGRAD)
		fcol = pixel_color_grd;
	if ((0 <= a->c.x && a->c.x < PIX_X && 0 <= a->c.y && a->c.y < PIX_Y)
		|| (0 <= b->c.x && b->c.x < PIX_X && 0 <= b->c.y && b->c.y < PIX_Y)
		|| cp[0] * cp[1] <= 0 || cp[0] * cp[2] <= 0 || cp[1] * cp[3] <= 0
		|| cp[2] * cp[3] <= 0)
		bresenham(dt, a, b, fcol);
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

int	plot_wires(t_data_fdf *dt)
{
	size_t	row;
	size_t	col;
	t_point	dst[2];

	t_point (*const src)[dt->map->cols] = (void *)dt->map->points;
	row = 0;
	while (++row < dt->map->rows)
	{
		col = dt->map->cols;
		while (col--)
			wire_visibility(dt, transform(dt->map, dst, &src[row - 1][col]),
				transform(dt->map, dst + 1, &src[row][col]));
	}
	col = 0;
	while (++col < dt->map->cols)
	{
		row = dt->map->rows;
		while (row--)
			wire_visibility(dt, transform(dt->map, dst, &src[row][col - 1]),
				transform(dt->map, dst + 1, &src[row][col]));
	}
	return (mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr,
			dt->img[dt->img_buffer].img_ptr, 0, 0));
}
