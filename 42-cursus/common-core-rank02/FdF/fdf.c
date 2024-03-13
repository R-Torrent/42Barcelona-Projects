/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/13 22:50:45 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// param[0]: void *mlx_ptr
// param[1]: void *win_ptr
// param[2]: t_map_fdf *map_fdf
int	key_hook(int keycode, t_map_fdf *map)
{
	keycode = ft_toupper(keycode);
	if (keycode == ESC)
		mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	else if (keycode == RL || keycode == UP || keycode == LF || keycode == DW
		|| keycode == RT || keycode == ZI || keycode == ZO || keycode == ZD
		|| keycode == ZU || keycode == CG)
	{
		mlx_clear_window(map->mlx_ptr, map->win_ptr);
		if (keycode == RL)
			isometric_projection(map, true);
		else if (keycode == UP)
			map->steps_shift[0]++;
		else if (keycode == LF)
			map->steps_shift[1]++;
		else if (keycode == DW)
			map->steps_shift[0]--;
		else if (keycode == RT)
			map->steps_shift[1]--;
		else if (keycode == ZI)
			map->steps_zoom++;
		else if (keycode == ZO)
			map->steps_zoom--;
		else if (keycode == ZD)
			scale_z0(map, ZR2, ZR1);
		else if (keycode == ZU)
			scale_z0(map, ZR1, ZR2);
		else if (keycode == CG)
			map->flags ^= CGRAD;
		plot_wires(map);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map_fdf	*map;
	int			exit_status;
	void		*mlx_ptr;

	if (argc != 2)
		exit(EXIT_FAILURE);
	exit_status = EXIT_FAILURE;
	mlx_ptr = mlx_init();
	if (!read_data(&map, argv[1]) && mlx_ptr)
	{
		map->mlx_ptr = mlx_ptr;
		map->win_ptr = mlx_new_window(mlx_ptr, PIX_Y, PIX_X, argv[1]);
		if (map->win_ptr)
		{
			isometric_projection(map, true);
			plot_wires(map);
			mlx_key_hook(map->win_ptr, key_hook, map);
			mlx_loop(mlx_ptr);
			exit_status = EXIT_SUCCESS;
		}
	}
	free(map);
	exit(exit_status);
}
