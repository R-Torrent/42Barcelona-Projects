/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:35:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/20 16:32:53 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	shift_view(t_map_fdf *map, int step_x, int step_y)
{
	int	zoom;
	int	shift;

	shift = DPK * map->zoom_fit[1] / map->zoom_fit[0];
	zoom = map->steps_zoom;
	while (zoom > 0)
	{
		shift = shift * ZR2 / ZR1;
		zoom--;
	}
	while (zoom < 0)
	{
		shift = shift * ZR1 / ZR2;
		zoom++;
	}
	map->view.x += step_x * shift;
	map->view.y += step_y * shift;
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

static int	distort_z(int steps_dz, int z)
{
	while (steps_dz > 0)
	{
		z = z * ZR1 / ZR2;
		steps_dz--;
	}
	while (steps_dz < 0)
	{
		z = z * ZR2 / ZR1;
		steps_dz++;
	}
	return (z);
}

// Third component after rotation, prior to projection:
// p->c.z = 1000 * (p->c0.x + p->c0.y + p->c0.z) / 1732;
void	isometric_projection(t_map_fdf *map, bool reset_view)
{
	t_point	*p;
	int		z1;
	int		limits[4];

	p = map->points + map->rows * map->cols;
	while (p-- > map->points)
	{
		z1 = distort_z(map->steps_dz, p->c0.z);
		p->c.x = 1000 * (p->c0.x + p->c0.y - (z1 << 1)) / 2449;
		p->c.y = 1000 * (-p->c0.x + p->c0.y) / 1414;
	}
	if (reset_view)
	{
		map->flags = 0;
		det_size(map, limits, map->zoom_fit);
		map->view.x = (limits[1] + limits[0]) / 2;
		map->view.y = (limits[3] + limits[2]) / 2;
		map->steps_zoom = 0;
	}
}
