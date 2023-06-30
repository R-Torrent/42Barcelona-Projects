/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:25:11 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/30 10:30:32 by rtorrent         ###   ########.fr       */
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

// 'libft' functions & structure needed for the project

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

void	ft_lstadd_back(t_list **plst, t_list *new);
void	ft_lstclear(t_list **plst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif
