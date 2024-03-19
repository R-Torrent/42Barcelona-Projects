/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/19 15:38:18 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	exit_fdf(t_data_fdf *data)
{
	if (data->img[0].img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img[0].img_ptr);
	if (data->img[1].img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img[1].img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->map);
	exit(data->exit_status);
}

static void	clear_image(void *mlx_ptr, struct s_img *img)
{
	int					x;
	int					y;
	char				*pixel;
	const int			bytes_per_pixel = img->bits_per_pixel / CHAR_BIT;
	const unsigned int	black = mlx_get_color_value(mlx_ptr, BLACK);

	x = PIX_X;
	while (x--)
	{
		y = PIX_Y;
		while (y--)
		{
			pixel = img->addr + (x * img->size_line + y * bytes_per_pixel);
			*(unsigned int *)pixel = black;
		}
	}
}

static void	transform_image(int keycode, t_data_fdf *data)
{
	if (keycode == RL)
		isometric_projection(data->map, true);
	else if (keycode == UP)
		shift_view(data->map, -1, 0);
	else if (keycode == LF)
		shift_view(data->map, 0, -1);
	else if (keycode == DW)
		shift_view(data->map, 1, 0);
	else if (keycode == RT)
		shift_view(data->map, 0, 1);
	else if (keycode == ZI)
		data->map->steps_zoom++;
	else if (keycode == ZO)
		data->map->steps_zoom--;
	else if (keycode == ZD)
		scale_z0(data->map, ZR2, ZR1);
	else if (keycode == ZU)
		scale_z0(data->map, ZR1, ZR2);
	else if (keycode == CG)
		data->map->flags ^= CGRAD;
	data->img_buffer ^= 1;
	clear_image(data->mlx_ptr, data->img + data->img_buffer);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	plot_wires(data);
}

static int	key_hook(int keycode, t_data_fdf *data)
{
	if (keycode == ESC)
		exit_fdf(data);
	else if (keycode == RL || keycode == UP || keycode == LF || keycode == DW
		|| keycode == RT || keycode == ZI || keycode == ZO || keycode == ZD
		|| keycode == ZU || keycode == CG)
		transform_image(keycode, data);
	return (0);
}

// 'KeyPress' event (2) + 'KeyPressMask' (1L << 0)
// 'Expose' event (12) + 'ExposureMask' (1L << 15)
// 'DestroyNotify' event (17) + 'StructureNotifyMask' (1L << 17)
int	main(int argc, char *argv[])
{
	t_data_fdf		fdf;

	fdf = (t_data_fdf){mlx_init(), NULL, EXIT_SUCCESS, 0,
		(struct s_img [2]){{NULL}, {NULL}}, NULL};
	if (argc == 2 && fdf.mlx_ptr && !read_data(&fdf.map, argv[1]))
	{
		fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, PIX_Y, PIX_X, argv[1]);
		fdf.img[0].img_ptr = mlx_new_image(fdf.mlx_ptr, PIX_Y, PIX_X);
		fdf.img[1].img_ptr = mlx_new_image(fdf.mlx_ptr, PIX_Y, PIX_X);
		if (fdf.win_ptr && fdf.img[0].img_ptr && fdf.img[1].img_ptr)
		{
			fdf.img[0].addr = mlx_get_data_addr(fdf.img[0].img_ptr, &fdf.img[0]
					.bits_per_pixel, &fdf.img[0].size_line, &fdf.img[0].endian);
			fdf.img[1].addr = mlx_get_data_addr(fdf.img[1].img_ptr, &fdf.img[1]
					.bits_per_pixel, &fdf.img[1].size_line, &fdf.img[1].endian);
			isometric_projection(fdf.map, true);
			plot_wires(&fdf);
			mlx_hook(fdf.win_ptr, 2, 1L << 0, key_hook, &fdf);
			mlx_hook(fdf.win_ptr, 12, 1L << 15, plot_wires, &fdf);
			mlx_hook(fdf.win_ptr, 17, 1L << 17, exit_fdf, &fdf);
			mlx_loop(fdf.mlx_ptr);
		}
	}
	fdf.exit_status = EXIT_FAILURE;
	exit_fdf(&fdf);
}
