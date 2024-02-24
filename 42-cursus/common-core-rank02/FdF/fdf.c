/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/24 20:12:25 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_data(t_map_points **pmap)
{
	int	fdfmap;

	if (argc != 2)
		exit(EXIT_FAILURE);
	fdfmap = open(argv[1], O_RDONLY);
	if (fdfmap == -1)
		exit(EXIT_FAILURE);
// PROGRAM GOES HERE
	if (close(fdfmap) == -1)
		exit(EXIT_FAILURE);	
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	int				map_fdf;
	t_map_points	*map_points;

	if (argc != 2)
		exit(EXIT_FAILURE);
	map_fdf = open(argv[1], O_RDONLY);
	if (map_fdf == -1)
		exit(EXIT_FAILURE);
	if (read_data(&map_points) || close(map_fdf) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
