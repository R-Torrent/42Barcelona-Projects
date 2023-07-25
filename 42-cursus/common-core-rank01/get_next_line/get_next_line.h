/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:25:11 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/25 01:40:59 by rtorrent         ###   ########.fr       */
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

// by default, maximum number of files that Mac OS X can open
# define MAX_FILES 12288

char	*get_next_line(int fd);

/* ************************************************************************** */

// 'libft' functions & structure needed for the project

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

void	ft_lstclear(t_list **plst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, size_t start, size_t len);

#endif
