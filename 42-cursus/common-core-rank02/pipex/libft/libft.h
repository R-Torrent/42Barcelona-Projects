/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:19:33 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/09 20:16:15 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ************************************************************************** */

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

// external declarations from the libc (AKA 'authorized functions')
void	free(void *ptr);
void	*malloc(size_t size);
ssize_t	read(int fildes, void *buf, size_t nbyte);
ssize_t	write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

// buffer size for read operations
// (=BUFSIZ constant defined in stdio.h)
// used in: ft_getnextline_fd
# define BUFFER_SIZE 1024

// by default, maximum number of files that Mac OS X can open
// used in: ft_getnextline_fd
# define MAX_FILES 12288

// minimim list size and subsequent batch allocations
// used in: ft_getnextline_fd
# define DEFAULT_LIST_SIZE 10

/* ************************************************************************** */

// functions also found in ctype.h
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

// functions also found in stdio.h
int		ft_printf(const char *s, ...);

// functions also found in stdlib.h
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);

// functions also found in string.h
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
char	*ft_strrchr(const char *s, int c);

// functions also found in strings.h
void	ft_bzero(void *s, size_t n);

/* ************************************************************************** */

// additional '42' functions
char	*ft_getnextline_fd(int fd);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(const char *s, char c);
void	ft_striteri(char *s, void (*f)(size_t, char *));
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strmapi(const char *s, char (*f)(size_t, char));
char	*ft_strtrim(const char *s, const char *set);
char	*ft_substr(const char *s, size_t start, size_t len);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;

// functions using type t_list (AKA 'bonus list functions')
void	ft_lstadd_back(t_list **plst, t_list *new);
void	ft_lstadd_front(t_list **plst, t_list *new);
void	ft_lstclear(t_list **plst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
size_t	ft_lstsize(t_list *lst);

/* ************************************************************************** */

#endif
