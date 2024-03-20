/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:05:25 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/20 19:48:06 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Mac version for the 42 Barcelona clusters

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

/*
	** NOTE ** The 'X' and 'Y' axes of the project form a right-handed system,
	contrary to the axes in the MiniLibX functions. This was done to reduce the
	mental burden of calculating expressions for the coordinates of any vector
	after two rotations.
*/

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

/*
	user options (ASCII codes)
	ESC = 'ESC' : window escape
	RL  = 'R' or 'r' : reload isometric projection
	UP  = 'W' or 'w' : move up
	LF  = 'A' or 'a' : move left
	DW  = 'S' or 's' : move down
	RT  = 'D' or 'd' : move right
	ZI  = 'Z' or 'z' : zoom in
	ZO  = 'X' or 'x' : zoom out
	ZD  = 'J' or 'j' : scale z down
	ZU  = 'K' or 'k' : scale z up
	CG  = 'C' or 'c' : toggle color gradation
*/
enum e_options
{
	ESC = 0x35,
	RL = 0xf,
	UP = 0xd,
	LF = 0x0,
	DW = 0x1,
	RT = 0x2,
	ZI = 0x6,
	ZO = 0x7,
	ZD = 0x26,
	ZU = 0x28,
	CG = 0x8
};

/*
	flags
	CGRAD : color gradation between endpoints enabled
*/
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
	int				steps_dz;
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
	int					exit_status;
	size_t				img_buffer;
	struct s_img		*img;
	struct s_map_fdf	*map;
}	t_data_fdf;

typedef unsigned int	(*t_fcol)(const t_point *, t_point *, const t_point *);

int				atoi2(const char *str, int *status);
unsigned int	atou2(const char *str, int *status);
int				cross_prod_sign(int vax, int vay, int vbx, int vby);
void			isometric_projection(t_map_fdf *map, bool reset_view);
unsigned int	pixel_color_grd(const t_point *a, t_point *p, const t_point *b);
unsigned int	pixel_color_smp(const t_point *a, t_point *p, const t_point *b);
int				plot_wires(t_data_fdf *data);
int				read_data(t_map_fdf **pmap, const char *file_fdf);
void			shift_view(t_map_fdf *map, int step_x, int step_y);
int				slope(int n0, int n1);

// additional 'libft' functions required for this project
// (stdlib.h the first, ctype.h the second, string.h the latter two)
int				ft_abs(int n);
int				ft_isxdigit(int c);
char			*ft_strtok(char *s, const char *delim);
char			*ft_strtok_r(char *s, const char *delim, char **saveptr);

/* ************************************************************************** */

#endif
