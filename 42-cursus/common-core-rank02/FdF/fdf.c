/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:48:07 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/19 14:29:34 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exit_fdf(t_data_fdf *data)
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
