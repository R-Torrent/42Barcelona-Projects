/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_wires.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:32:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/07 21:33:30 by rtorrent         ###   ########.fr       */
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
static void	bresenham(void *mlx_ptr, void *win_ptr, t_point p0, t_point p1)
{
	const int	d[2] = {ft_abs(p1.x - p0.x), -ft_abs(p1.y - p0.y)};
	const int	s[2] = {slope(p0.x, p1.x), slope(p0.y, p1.y)};
	int			error;
	int			e2;

	error = d[0] + d[1];
	while (true)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, p0.x, p0.y, WHITE);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = error << 1;
		if (e2 >= d[1])
		{
			if (p0.x == p1.x)
				break ;
			error += d[1];
			p0.x += s[0];
		}
		if (e2 <= d[0])
		{
			if (p0.y == p1.y)
				break ;
			error += d[0];
			p0.y += s[1];
		}
	}
}

void	plot_wires(void *mlx_ptr, void *win_ptr, t_map_fdf *map_fdf)
{
	size_t	row;
	size_t	col;
	t_point (*const p)[map_fdf->rows] = ((*)[map_fdf->rows])map_fdf->points;

	row = 1;
	while (row < map_fdf->rows)
	{
		col = 0;
		while (col < map_fdf->cols)
			bresenham(mlx_ptr, win_ptr, p[row - 1][col], p[row][col]);
	}
	col = 1;
	while (col < map_fdf->cols)
	{
		row = 0;
		while (row < map_fdf->rows)
			bresenham(mlx_ptr, win_ptr, p[row][col - 1], p[row][col]);
	}
}
