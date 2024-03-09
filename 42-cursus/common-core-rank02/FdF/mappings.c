/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:35:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/09 04:25:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scaling(t_map_fdf *map_fdf, int num, int den)
{
	t_point	*p;

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		p->c1.x = p->c1.x * num / den;
		p->c1.y = p->c1.y * num / den;
		p->c1.z = p->c1.z * num / den;
	}
}

void	htranslation(t_map_fdf *map_fdf, int dx, int dy)
{
	t_point	*p;

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		p->c1.x += dx;
		p->c1.y += dy;
	}
}

void	fit_screen_size(t_map_fdf *map_fdf, int size_x, int size_y)
{
	t_point	*p;
	int		limits[4];

	limits[0] = map_fdf->points->c1.x;
	limits[1] = limits[0];
	limits[2] = map_fdf->points->c1.y;
	limits[3] = limits[2];
	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		if (p->c1.x < limits[0])
			limits[0] = p->c1.x;
		else if (p->c1.x > limits[1])
			limits[1] = p->c1.x;
		if (p->c1.y < limits[2])
			limits[2] = p->c1.y;
		else if (p->c1.y > limits[3])
			limits[3] = p->c1.y;
	}
	htranslation(map_fdf, -limits[0], -limits[2]);
	if ((limits[1] - limits[0]) * size_y < (limits[3] - limits[2]) * size_x)
		scaling(map_fdf, size_y, limits[3] - limits[2]);
	else
		scaling(map_fdf, size_x, limits[1] - limits[0]);
}

// includes a 100,000-factor rescale, to mantain significant digits in the map
void	isometric_projection(t_map_fdf *map_fdf)
{
	t_point	*p;

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		p->c1.x = 40825 * (p->c0.x + p->c0.y - (p->c0.z << 1));
		p->c1.y = 70711 * (-p->c0.x + p->c0.y);
		p->c1.z = 57735 * (p->c0.x + p->c0.y + p->c0.z);
	}
}
