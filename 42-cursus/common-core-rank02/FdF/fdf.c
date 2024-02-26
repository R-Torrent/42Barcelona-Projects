/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/26 20:39:46 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_map_fdf	*map_fdf;

	if (argc != 2)
		exit(EXIT_FAILURE);
	if (read_data(&map_fdf, argv[1]))
		exit(EXIT_FAILURE);
// GRAPHIC STUFF
	free(map_fdf);
	exit(EXIT_SUCCESS);
}
