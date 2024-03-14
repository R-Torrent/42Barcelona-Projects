/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/14 04:48:17 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_data_fdf *data)
{
	keycode = ft_toupper(keycode);
	if (keycode == ESC)
	{
		mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	}
	else if (keycode == RL || keycode == UP || keycode == LF || keycode == DW
		|| keycode == RT || keycode == ZI || keycode == ZO || keycode == ZD
		|| keycode == ZU || keycode == CG)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		fdf_clear_image(data->mlx_ptr, data->img);
		if (keycode == RL)
			isometric_projection(data->map, true);
		else if (keycode == UP)
			data->map->steps_shift[0]++;
		else if (keycode == LF)
			data->map->steps_shift[1]++;
		else if (keycode == DW)
			data->map->steps_shift[0]--;
		else if (keycode == RT)
			data->map->steps_shift[1]--;
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
		plot_wires(data);
	}
	return (0);
}

unsigned int	fdf_pixel(struct s_img *img, int x, int y, unsigned int color)
{
	char		*pixel;
	const int	bytes_per_pixel = img->bits_per_pixel >> 3;

	pixel = img->addr + (x * img->size_line + y * bytes_per_pixel);
	*(unsigned int *)pixel = color;
	return (color);
}

void	fdf_clear_image(void *mlx_ptr, struct s_img *img)
{
	int					x;
	int					y;
	char				*pixel;
	const int			bytes_per_pixel = img->bits_per_pixel >> 3;
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

int	main(int argc, char *argv[])
{
	t_data_fdf		fdf;
	struct s_img	img;
	int				exit_status;

	exit_status = EXIT_FAILURE;
	if (argc == 2)
	{
		fdf.mlx_ptr = mlx_init();
		if (!read_data(&fdf, argv[1]) && fdf.mlx_ptr)
		{
			fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, PIX_Y, PIX_X, argv[1]);
			img.img_ptr = mlx_new_image(fdf.mlx_ptr, PIX_Y, PIX_X);
			if (fdf.win_ptr && img.img_ptr)
			{
				img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
						&img.size_line, &img.endian);
				fdf.img = &img;
				isometric_projection(fdf.map, true);
				plot_wires(&fdf);
				mlx_key_hook(fdf.win_ptr, key_hook, &fdf);
				mlx_loop(fdf.mlx_ptr);
				exit_status = EXIT_SUCCESS;
			}
		}
		free(fdf.map);
	}
	exit(exit_status);
}
