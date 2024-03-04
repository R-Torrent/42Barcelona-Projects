/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/04 02:52:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, void *param[2])
{
	if (keycode == ESC)
		mlx_destroy_window(param[0], param[1]);
	return (0);
}

void	fit_screen_size(t_map *map_fdf, int size_x, int size_y)
{

}

// includes a 1000-factor rescale, to mantain significant digits in the map
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
	void		*mlx_ptr;
	void		*win_ptr;

	if (argc != 2)
		exit(EXIT_FAILURE);
	if (read_data(&map_fdf, argv[1]))
		exit(EXIT_FAILURE);
	isometric_projection(map_fdf);
	fit_screen_size(map_fdf, PIX_X, PIX_Y);
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		exit(EXIT_FAILURE);
	win_ptr = mlx_new_window(mlx_ptr, PIX_X, PIX_Y, "FdF");
	if (!win_ptr)
		exit(EXIT_FAILURE);

// GRAPHIC stuff, such as
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xffffff);

	mlx_key_hook(win_ptr, key_hook, (void *)(void *[2]){mlx_ptr, win_ptr});
	free(map_fdf);
	mlx_loop(mlx_ptr);
	exit(EXIT_SUCCESS);
}
