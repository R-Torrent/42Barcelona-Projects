/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:05:25 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/23 18:50:35 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"

/* ************************************************************************** */

# include <fcntl.h>
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

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}	t_point;

typedef struct s_map_points
{
	unsigned int	rows;
	unsigned int	cols;
	t_point			points[];
}	t_map_points;

#endif
