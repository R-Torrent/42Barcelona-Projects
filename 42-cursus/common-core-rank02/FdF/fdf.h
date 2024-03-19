/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:05:25 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/19 01:38:59 by rtorrent         ###   ########.fr       */
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

// default window size, in pixels
# define PIX_X 450
# define PIX_Y 600

// image center, in pixels
# define ICEN_X 225
# define ICEN_Y 300

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
enum e_options
{
// 'ESC': window escape
	ESC = 0xff1b,
// 'R' or 'r': reload isometric projection
	RL = 0x72,
// 'W' or 'w': move up
	UP = 0x77,
// 'A' or 'a': move left
	LF = 0x61,
// 'S' or 's': move down
	DW = 0x73,
// 'D' or 'd': move right
	RT = 0x64,
// 'Z' or 'z': zoom in
	ZI = 0x7a,
// 'X' or 'x': zoom out
	ZO = 0x78,
// 'J' or 'j': scale z down
	ZD = 0x6a,
// 'K' or 'k': scale z up
	ZU = 0x6b,
// 'C' or 'c' toggle color gradation
	CG = 0x63
};

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

struct s_coord3
{
	int	x;
	int	y;
	int	z;
};

struct s_coord2
{
	int	x;
	int	y;
};

typedef struct s_point
{
	struct s_coord3	c0;
	struct s_coord2	c;
	unsigned int	color_trgb;
}	t_point;

typedef struct s_map_fdf
{
	unsigned int	flags;
	size_t			rows;
	size_t			cols;
	int				steps_zoom;
	int				zoom_fit[2];
	struct s_coord2	view;
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
	size_t				img_buffer;
	struct s_img		*img;
	struct s_map_fdf	*map;
}	t_data_fdf;

typedef unsigned int	(*t_fcol)(const t_point *, t_point *, const t_point *);

int				atoi2(const char *str, int *status);
unsigned int	atou2(const char *str, int *status);
int				cross_prod_sign(int vax, int vay, int vbx, int vby);
void			fdf_clear_image(void *mlx_ptr, struct s_img *img);
unsigned int	fdf_pixel(void *mlx_ptr, struct s_img *img, int *x,
					unsigned int color_trgb);
void			isometric_projection(t_map_fdf *map, bool reset_view);
unsigned int	pixel_color_grd(const t_point *a, t_point *p, const t_point *b);
unsigned int	pixel_color_smp(const t_point *a, t_point *p, const t_point *b);
void			plot_wires(t_data_fdf *data);
int				read_data(t_map_fdf **pmap, const char *file_fdf);
void			scale_z0(t_map_fdf *map, int num, int den);
void			shift_view(t_map_fdf *map, int step_x, int step_y);

// additional 'libft' functions required for this project
// (stdlib.h the first, ctype.h the second, string.h the latter two)
int				ft_abs(int n);
int				ft_isxdigit(int c);
char			*ft_strtok(char *s, const char *delim);
char			*ft_strtok_r(char *s, const char *delim, char **saveptr);

/* ************************************************************************** */

#endif
