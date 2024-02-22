/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:05:25 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/22 21:00:50 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"

/* ************************************************************************** */

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

#endif
