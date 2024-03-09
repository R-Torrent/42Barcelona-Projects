/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/09 03:29:13 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// param[0]: t_map_fdf *map_fdf
// param[1]: void *mlx_ptr
// param[2]: void *win_ptr
int	key_hook(int keycode, void *param[])
{
	keycode = ft_toupper(keycode);
	if (keycode == ESC)
		mlx_destroy_window(param[0], param[1]);
	else if (keycode == RL || keycode == UP || keycode == LF || keycode == DW
		|| keycode == RT || keycode == ZI || keycode == ZO)
	{
		mlx_clear_window(param[0], param[1]);
		if (keycode == RL)
		{
			((t_map_fdf *)param[2])->d_x = 0;
			((t_map_fdf *)param[2])->d_y = 0;
			((t_map_fdf *)param[2])->zoom = 0;
		}
		if (keycode == UP)
			((t_map_fdf *)param[2])->d_x--;
		else if (keycode == LF)
			((t_map_fdf *)param[2])->d_y--;
		else if (keycode == DW)
			((t_map_fdf *)param[2])->d_x++;
		else if (keycode == RT)
			((t_map_fdf *)param[2])->d_y++;
		else if (keycode == ZI)
			((t_map_fdf *)param[2])->zoom++;
		else if (keycode == ZO)
			((t_map_fdf *)param[2])->zoom--;
		plot_wires(param[0], param[1], param[2]);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map_fdf	*map_fdf;
	void		*mlx_ptr;
	void		*win_ptr;
	int			exit_status;

	if (argc != 2)
		exit(EXIT_FAILURE);
	exit_status = EXIT_FAILURE;
	mlx_ptr = mlx_init();
	if (!read_data(&map_fdf, argv[1]) && mlx_ptr)
	{
		win_ptr = mlx_new_window(mlx_ptr, PIX_X, PIX_Y, TITLE);
		if (win_ptr)
		{
			isometric_projection(map_fdf);
			fit_screen_size(map_fdf, PIX_X, PIX_Y);
			plot_wires(mlx_ptr, win_ptr, map_fdf);
			mlx_key_hook(win_ptr, key_hook,
				(void *[3]){mlx_ptr, win_ptr, map_fdf});
			mlx_loop(mlx_ptr);
			exit_status = EXIT_SUCCESS;
		}
	}
	free(map_fdf);
	exit(exit_status);
}
