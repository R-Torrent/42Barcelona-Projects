/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:05:25 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/05 03:29:10 by rtorrent         ###   ########.fr       */
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
# define PIX_X 500
# define PIX_Y 375

// ASCII code for the 'ESC' key
# define ESC 0x1b

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

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}	t_point;

typedef struct s_map_points
{
	size_t		rows;
	size_t		cols;
	t_point		points[];
}	t_map_fdf;

int		read_data(t_map_fdf **pmap, const char *file_fdf);

// additional 'libft' functions required for this project
// (ctype.h the first, string.h the latter two)
int		ft_isxdigit(int c);
char	*ft_strtok(char *s, const char *delim);
char	*ft_strtok_r(char *s, const char *delim, char **saveptr);

/* ************************************************************************** */

#endif
