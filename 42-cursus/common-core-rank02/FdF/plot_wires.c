/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_wires.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:32:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/11 19:56:44 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	slope(int n0, int n1)
{
	if (n0 < n1)
		return (1);
	return (-1);
}

// version of Bresenham's algorithm, as found in
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
static void	bresnhm(void *mlx, void *win, struct s_coord p0, struct s_coord p1)
{
	const int	d[2] = {ft_abs(p1.x - p0.x), -ft_abs(p1.y - p0.y)};
	const int	s[2] = {slope(p0.x, p1.x), slope(p0.y, p1.y)};
	int			error[2];

	error[0] = d[0] + d[1];
	while (mlx_pixel_put(mlx, win, p0.y, p0.x, WHITE))
	{
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		error[1] = error[0] << 1;
		if (error[1] >= d[1])
		{
			if (p0.x == p1.x)
				break ;
			error[0] += d[1];
			p0.x += s[0];
		}
		if (error[1] <= d[0])
		{
			if (p0.y == p1.y)
				break ;
			error[0] += d[0];
			p0.y += s[1];
		}
	}
}

static struct s_coord	tr(t_map_fdf *map, t_point *point)
{
	struct s_coord	coord;
	int				zoom;

	coord.x = point->c1.x + map->shift[0];
	coord.y = point->c1.y + map->shift[1];
	zoom = map->steps_zoom;
	while (zoom > 0)
	{
		coord.x = coord.x * ZR1 / ZR2;
		coord.y = coord.y * ZR1 / ZR2;
		zoom--;
	}
	while (zoom < 0)
	{
		coord.x = coord.x * ZR2 / ZR1;
		coord.y = coord.y * ZR2 / ZR1;
		zoom++;
	}
	coord.x = coord.x * map->zoom_fit[0] / map->zoom_fit[1];
	coord.y = coord.y * map->zoom_fit[0] / map->zoom_fit[1];
	coord.x += map->steps_shift[0] * DPK;
	coord.y += map->steps_shift[1] * DPK;
	return (coord);
}

void	plot_wires(void *mlx, void *win, t_map_fdf *map)
{
	size_t	row;
	size_t	col;

	t_point (*const p)[map->cols] = (void *)map->points;
	row = 0;
	while (++row < map->rows)
	{
		col = 0;
		while (col < map->cols)
		{
			bresnhm(mlx, win, tr(map, &p[row - 1][col]), tr(map, &p[row][col]));
			col++;
		}
	}
	col = 0;
	while (++col < map->cols)
	{
		row = 0;
		while (row < map->rows)
		{
			bresnhm(mlx, win, tr(map, &p[row][col - 1]), tr(map, &p[row][col]));
			row++;
		}
	}
}
