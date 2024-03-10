/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:35:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/10 19:44:25 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_z0(t_map_fdf *map_fdf, int num, int den)
{
	t_point	*p;

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
		p->c0.z = p->c0.z * num / den;
	isometric_projection(map_fdf, false);
}

static void	det_size(t_map_fdf *map_fdf, long limits[], long zoom_fit[])
{
	t_point	*p;

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
	zoom_fit[0] = PIX_X;
	zoom_fit[1] = limits[1] - limits[0];
	if ((limits[1] - limits[0]) * PIX_Y < (limits[3] - limits[2]) * PIX_X)
	{
		zoom_fit[0] = PIX_Y;
		zoom_fit[1] = limits[3] - limits[2];
	}
}

void	isometric_projection(t_map_fdf *map_fdf, bool reset_view)
{
	t_point	*p;
	long	limits[4];

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p-- > map_fdf->points)
	{
		p->c1.x = (p->c0.x + p->c0.y - (p->c0.z << 1)) / 244949L;
		p->c1.y = (-p->c0.x + p->c0.y) / 141421L;
		p->c1.z = (p->c0.x + p->c0.y + p->c0.z) / 173205L;
	}
	if (reset_view)
	{
		det_size(map_fdf, limits, map_fdf->zoom_fit);
		map_fdf->shift[0] = -limits[0];
		map_fdf->shift[1] = -limits[2];
		map_fdf->steps_shift[0] = 0;
		map_fdf->steps_shift[1] = 0;
		map_fdf->steps_zoom = 0;
	}
}
