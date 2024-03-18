/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/18 03:03:03 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_fdf(t_data_fdf *data, int exit_status)
{
	if (data->img->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->map);
	exit(exit_status);
}

unsigned int	fdf_pixel(void *mlx_ptr, struct s_img *img, int *x,
	unsigned int color_trgb)
{
	char		*pixel;
	const int	bytes_per_pixel = img->bits_per_pixel / CHAR_BIT;

	if (x[0] >= 0 && x[0] < PIX_X && x[1] >= 0 && x[1] < PIX_Y)
	{
		pixel = img->addr + (x[0] * img->size_line + x[1] * bytes_per_pixel);
		*(unsigned int *)pixel = mlx_get_color_value(mlx_ptr, color_trgb);
	}
	return (color_trgb);
}

void	fdf_clear_image(void *mlx_ptr, struct s_img *img)
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

int	key_hook(int keycode, t_data_fdf *data)
{
	if (keycode == ESC)
		exit_fdf(data, EXIT_SUCCESS);
	else if (keycode == RL || keycode == UP || keycode == LF || keycode == DW
		|| keycode == RT || keycode == ZI || keycode == ZO || keycode == ZD
		|| keycode == ZU || keycode == CG)
	{
		mlx_clear_window(data->mlx_ptr, data->win_ptr);
		fdf_clear_image(data->mlx_ptr, data->img);
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
		plot_wires(data);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data_fdf		fdf;
	struct s_img	img;

	fdf = (t_data_fdf){mlx_init(), NULL, &img, NULL};
	img.img_ptr = NULL;
	if (argc == 2 && fdf.mlx_ptr && !read_data(&fdf.map, argv[1]))
	{
		fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, PIX_Y, PIX_X, argv[1]);
		img.img_ptr = mlx_new_image(fdf.mlx_ptr, PIX_Y, PIX_X);
		if (fdf.win_ptr && img.img_ptr)
		{
			img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel,
					&img.size_line, &img.endian);
			isometric_projection(fdf.map, true);
			plot_wires(&fdf);
			mlx_key_hook(fdf.win_ptr, key_hook, &fdf);
			mlx_loop(fdf.mlx_ptr);
		}
	}
	exit_fdf(&fdf, EXIT_FAILURE);
}
