/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:05:25 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/14 04:43:38 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

/* ************************************************************************** */

# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

// external declarations from the libc (AKA 'authorized functions')
int				close(int fildes);
void			exit(int status);
void			free(void *ptr);
void			*malloc(size_t size);
int				open(const char *pathname, int flags, ...);
void			perror(const char *s);
ssize_t			read(int fildes, void *buf, size_t nbyte);
char			*strerror(int errnum);
ssize_t			write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

// ** NOTE ** The 'X' and 'Y' axes of the project form a right-handed system,
// contrary to the axes in the MiniLibX functions. This was done to reduce the
// mental burden of calculating expressions for the coordinates of any vector
// after two rotations.

// default screen size, in pixels
# define PIX_X 450
# define PIX_Y 600

// base scale for all dimensions
# define BSCALE 200
// ratio of horizontal dimensions to altitude
# define XYSCALE 1

// displacement per keystroke (pixels)
# define DPK 30

// zoom ratio per keystroke, ZR1:ZR2
# define ZR1 20
# define ZR2 19

// user options (ASCII codes):
// 'ESC': window escape
# define ESC 0x1b
// 'R' or 'r': reload isometric projection
# define RL 0x52
// 'W' or 'w': move up
# define UP 0x57
// 'A' or 'a': move left
# define LF 0x41
// 'S' or 's': move down
# define DW 0x53
// 'D' or 'd': move right
# define RT 0x44
// 'Z' or 'z': zoom in
# define ZI 0x5a
// 'X' or 'x': zoom out
# define ZO 0x58
// 'J' or 'j': scale z down
# define ZD 0x4a
// 'K' or 'k': scale z up
# define ZU 0x4b
// 'C' or 'c' toggle color gradation
# define CG 0x43

// flags
// color gradation between endpoints
# define CGRAD 01

enum e_colors
{
	BLACK = 0x000000,
	GRAY = 0x808080,
	WHITE = 0xffffff,
	RED = 0xff0000,
	GREEN = 0x00ff00,
	BLUE = 0x0000ff,
	CYAN = 0x00ffff,
	MAGENTA = 0xff00ff,
	YELLOW = 0xffff00
};

struct s_coord
{
	int	x;
	int	y;
	int	z;
};

typedef struct s_point
{
	struct s_coord	c0;
	struct s_coord	c1;
	unsigned int	color;
}	t_point;

typedef struct s_map_fdf
{
	unsigned int	flags;
	size_t			rows;
	size_t			cols;
	int				steps_shift[2];
	int				steps_zoom;
	int				shift[2];
	int				zoom_fit[2];
	t_point			points[];
}	t_map_fdf;

struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
};

typedef struct s_data_fdf
{
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_img		*img;
	struct s_map_fdf	*map;
}	t_data_fdf;

typedef unsigned int	(*t_fcol)(const t_point *, t_point *, const t_point *);

void			fdf_clear_image(void *mlx_ptr, struct s_img *img);
unsigned int	fdf_pixel(struct s_img *img, int x, int y, unsigned int color);
void			isometric_projection(t_map_fdf *map, bool reset_view);
unsigned int	pixel_color_grd(const t_point *a, t_point *p, const t_point *b);
unsigned int	pixel_color_smp(const t_point *a, t_point *p, const t_point *b);
void			plot_wires(t_data_fdf *data);
int				read_data(t_data_fdf *data, const char *file_fdf);
void			scale_z0(t_map_fdf *map, int num, int den);

// additional 'libft' functions required for this project
// (stdlib.h the first, ctype.h the second, string.h the latter two)
int				ft_abs(int n);
int				ft_isxdigit(int c);
char			*ft_strtok(char *s, const char *delim);
char			*ft_strtok_r(char *s, const char *delim, char **saveptr);

/* ************************************************************************** */

#endif
