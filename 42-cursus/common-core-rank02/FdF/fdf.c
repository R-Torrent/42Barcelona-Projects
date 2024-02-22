/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/22 21:24:46 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
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
