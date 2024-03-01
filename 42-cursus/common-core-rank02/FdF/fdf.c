/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/01 14:19:35 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric_projection(t_map_fdf *map_fdf)
{
	t_point	*p;
	int		xip;
	int		yip;

	p = map_fdf->points + map_fdf->rows * map_fdf->cols;
	while (p >= map_fdf->points)
	{
		p--;
		xip = 707 * (p->x - p->z);
		yip = 408 * (p->x + (p->y << 1) + p->z);
		p->x = xip;
		p->y = yip;
		p->z = 0;
	}
}

int	main(int argc, char *argv[])
{
	t_map_fdf	*map_fdf;

	if (argc != 2)
		exit(EXIT_FAILURE);
	if (read_data(&map_fdf, argv[1]))
		exit(EXIT_FAILURE);
	isometric_projection(map_fdf);
// GRAPHIC STUFF
	free(map_fdf);
	exit(EXIT_SUCCESS);
}
