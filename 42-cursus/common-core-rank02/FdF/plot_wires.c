/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_wires.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:32:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/14 04:49:10 by rtorrent         ###   ########.fr       */
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
static void	bresnhm(t_data_fdf *data, t_point a, t_point b, t_fcol fcol)
{
	const t_point	a0 = a;
	const int		d[2] = {ft_abs(b.c1.x - a.c1.x), -ft_abs(b.c1.y - a.c1.y)};
	const int		s[2] = {slope(a.c1.x, b.c1.x), slope(a.c1.y, b.c1.y)};
	int				error[2];

	error[0] = d[0] + d[1];
	while (fdf_pixel(data->img, a.c1.x, a.c1.y, fcol(&a0, &a, &b))
		&& (a.c1.x != b.c1.x || a.c1.y != b.c1.y))
	{
		error[1] = error[0] << 1;
		if (error[1] >= d[1])
		{
			if (a.c1.x == b.c1.x)
				break ;
			error[0] += d[1];
			a.c1.x += s[0];
		}
		if (error[1] <= d[0])
		{
			if (a.c1.y == b.c1.y)
				break ;
			error[0] += d[0];
			a.c1.y += s[1];
		}
	}
}

static t_point	tr(t_map_fdf *map, const t_point *point)
{
	t_point	point_tr;
	int		zoom;

	point_tr = *point;
	point_tr.c1.x += map->shift[0];
	point_tr.c1.y += map->shift[1];
	zoom = map->steps_zoom;
	while (zoom > 0)
	{
		point_tr.c1.x = point_tr.c1.x * ZR1 / ZR2;
		point_tr.c1.y = point_tr.c1.y * ZR1 / ZR2;
		zoom--;
	}
	while (zoom < 0)
	{
		point_tr.c1.x = point_tr.c1.x * ZR2 / ZR1;
		point_tr.c1.y = point_tr.c1.y * ZR2 / ZR1;
		zoom++;
	}
	point_tr.c1.x = point_tr.c1.x * map->zoom_fit[0] / map->zoom_fit[1];
	point_tr.c1.y = point_tr.c1.y * map->zoom_fit[0] / map->zoom_fit[1];
	point_tr.c1.x += map->steps_shift[0] * DPK;
	point_tr.c1.y += map->steps_shift[1] * DPK;
	return (point_tr);
}

void	plot_wires(t_data_fdf *dt)
{
	t_map_fdf *const	map = dt->map;
	size_t				row;
	size_t				col;
	t_fcol				fcol;

	if (dt->map->flags & CGRAD)
		fcol = pixel_color_grd;
	else
		fcol = pixel_color_smp;
	t_point (*const p)[map->cols] = (void *)map->points;
	row = 0;
	while (++row < map->rows)
	{
		col = map->cols;
		while (col--)
			bresnhm(dt, tr(map, &p[row - 1][col]), tr(map, &p[row][col]), fcol);
	}
	col = 0;
	while (++col < map->cols)
	{
		row = map->rows;
		while (row--)
			bresnhm(dt, tr(map, &p[row][col - 1]), tr(map, &p[row][col]), fcol);
	}
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img->img_ptr, 0, 0);
}
