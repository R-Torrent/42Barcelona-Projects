/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:57:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/19 13:37:39 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	key_hook(int keycode, t_data_fdf *data)
{
	if (keycode == ESC)
		exit_fdf(data);
	else if (keycode == RL || keycode == UP || keycode == LF || keycode == DW
		|| keycode == RT || keycode == ZI || keycode == ZO || keycode == ZD
		|| keycode == ZU || keycode == CG)
		transform_image(keycode, data);
	return (0);
}
