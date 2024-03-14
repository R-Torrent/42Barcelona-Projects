/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:35:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/14 14:21:39 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_z0(t_map_fdf *map, int num, int den)
{
	t_point	*p;

	p = map->points + map->rows * map->cols;
	while (p-- > map->points)
		p->c0.z = p->c0.z * num / den;
	isometric_projection(map, false);
}

static void	det_size(t_map_fdf *map, int limits[], int zoom_fit[])
{
	t_point	*p;

	limits[0] = map->points->c.x;
	limits[1] = limits[0];
	limits[2] = map->points->c.y;
	limits[3] = limits[2];
	p = map->points + map->rows * map->cols;
	while (p-- > map->points)
	{
		if (p->c.x < limits[0])
			limits[0] = p->c.x;
		else if (p->c.x > limits[1])
			limits[1] = p->c.x;
		if (p->c.y < limits[2])
			limits[2] = p->c.y;
		else if (p->c.y > limits[3])
			limits[3] = p->c.y;
	}
	zoom_fit[0] = PIX_X;
	zoom_fit[1] = limits[1] - limits[0];
	if ((limits[1] - limits[0]) * PIX_Y < (limits[3] - limits[2]) * PIX_X)
	{
		zoom_fit[0] = PIX_Y;
		zoom_fit[1] = limits[3] - limits[2];
	}
}

void	isometric_projection(t_map_fdf *map, bool reset_view)
{
	t_point	*p;
	int		limits[4];

	p = map->points + map->rows * map->cols;
	while (p-- > map->points)
	{
		p->c.x = 1000 * (p->c0.x + p->c0.y - (p->c0.z << 1)) / 2449;
		p->c.y = 1000 * (-p->c0.x + p->c0.y) / 1414;
		p->c.z = 1000 * (p->c0.x + p->c0.y + p->c0.z) / 1732;
	}
	if (reset_view)
	{
		map->flags = 0;
		det_size(map, limits, map->zoom_fit);
		map->shift[0] = -limits[0];
		map->shift[1] = -limits[2];
		map->steps_shift[0] = 0;
		map->steps_shift[1] = 0;
		map->steps_zoom = 0;
	}
}
