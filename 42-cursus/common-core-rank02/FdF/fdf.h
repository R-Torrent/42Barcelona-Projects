/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:05:25 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/09 03:57:51 by rtorrent         ###   ########.fr       */
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
int		close(int fildes);
void	exit(int status);
void	free(void *ptr);
void	*malloc(size_t size);
int		open(const char *pathname, int flags, ...);
void	perror(const char *s);
ssize_t	read(int fildes, void *buf, size_t nbyte);
char	*strerror(int errnum);
ssize_t	write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

// default screen size, in pixels
# define PIX_X 600
# define PIX_Y 450

// window title
# define TITLE "FdF"

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
// 'J' or 'j': zoom in
# define ZI 0x4a
// 'K' or 'k': zoom out
# define ZO 0x4b

// displacement per keystroke
# define DPM 5

// zoom ratio per keystroke, ZR1:ZR2
# define ZR1 20
# define ZR2 19

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
	size_t			rows;
	size_t			cols;
	unsigned int	flags;
	int				d_x;
	int				d_y;
	int				zoom;
	t_point			points[];
}	t_map_fdf;

void	plot_wires(void *mlx_ptr, void *win_ptr, t_map_fdf *map_fdf);
void	fit_screen_size(t_map_fdf *map_fdf, int size_x, int size_y);
void	isometric_projection(t_map_fdf *map_fdf);
void	htranslation(t_map_fdf *map_fdf, int dx, int dy);
int		read_data(t_map_fdf **pmap, const char *file_fdf);
void	scaling(t_map_fdf *map_fdf, int num, int den);

// additional 'libft' functions required for this project
// (stdlib.h the first, ctype.h the second, string.h the latter two)
int		ft_abs(int n);
int		ft_isxdigit(int c);
char	*ft_strtok(char *s, const char *delim);
char	*ft_strtok_r(char *s, const char *delim, char **saveptr);

/* ************************************************************************** */

#endif
