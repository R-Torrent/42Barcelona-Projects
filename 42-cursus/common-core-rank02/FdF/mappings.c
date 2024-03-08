/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:35:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/08 18:46:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scaling(t_map_fdf *map_fdf, int num, int den)
{
	t_point	*p;

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		p->x = p->x * num / den;
		p->y = p->y * num / den;
		p->z = p->z * num / den;
	}
}

void	htranslation(t_map_fdf *map_fdf, int dx, int dy)
{
	t_point	*p;

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		p->x += dx;
		p->y += dy;
	}
}

void	fit_screen_size(t_map_fdf *map_fdf, int size_x, int size_y)
{
	t_point	*p;
	int		limits[4];

	limits[0] = map_fdf->points->x;
	limits[1] = limits[0];
	limits[2] = map_fdf->points->y;
	limits[3] = limits[2];
	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		if (p->x < limits[0])
			limits[0] = p->x;
		else if (p->x > limits[1])
			limits[1] = p->x;
		if (p->y < limits[2])
			limits[2] = p->y;
		else if (p->y > limits[3])
			limits[3] = p->y;
	}
	htranslation(map_fdf, -limits[0], -limits[2]);
	if ((limits[1] - limits[0]) * size_y < (limits[3] - limits[2]) * size_x)
		scaling(map_fdf, size_y, limits[3] - limits[2]);
	else
		scaling(map_fdf, size_x, limits[1] - limits[0]);
}

// includes a 1000-factor rescale, to mantain significant digits in the map
void	isometric_projection(t_map_fdf *map_fdf)
{
	t_point	*p;

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		p->x = 408 * (p->x0 + p->y0 - (p->z0 << 1));
		p->y = 707 * (-p->x0 + p->y0);
		p->z = 577 * (p->x0 + p->y0 + p->z0);
	}
}
