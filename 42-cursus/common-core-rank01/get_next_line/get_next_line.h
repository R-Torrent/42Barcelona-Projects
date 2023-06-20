/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:25:11 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/20 16:40:36 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* ************************************************************************** */

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

// library functions & structure needed for the project

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

void	ft_lstadd_back(t_list **plst, t_list *new);
t_list	*ft_lstnew(void *content);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif
