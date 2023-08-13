/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:25:11 by rtorrent          #+#    #+#             */
/*   Updated: 2023/08/12 15:40:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* ************************************************************************** */

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

// external declarations from the libc (AKA 'authorized functions')
void	free(void *ptr);
void	*malloc(size_t size);
ssize_t	read(int fildes, void *buf, size_t nbyte);

/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# ifndef DEFAULT_LIST_SIZE
#  define DEFAULT_LIST_SIZE 10
# endif

// by default, maximum number of files that Mac OS X can open
# define MAX_FILES 12288

typedef struct s_block
{
	size_t			len;
	unsigned int	index;
	struct s_block	*prev;
	char			*start;
	char			str[BUFFER_SIZE];
}	*t_blocks;

char	*get_next_line(int fd);

/* ************************************************************************** */

// 'libft' functions (string.h) needed for the project

void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);

/* ************************************************************************** */

#endif
