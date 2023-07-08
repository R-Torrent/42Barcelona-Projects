/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/08 17:31:01 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*construct_line(t_list **plst)
{
	t_list	*lst;
	size_t	size;
	char	*p0;
	char	*p;

	if (!*plst)
		return (NULL);
	lst = *plst;
	size = 0;
	while (lst->next)
	{
		size += BUFFER_SIZE;
		lst = lst->next;
	}
	p0 = malloc(size + ft_strlcpy(NULL, lst->content, 0) + 1);
	p = p0;
	lst = *plst;
	while (p0 && lst)
	{
		p += ft_strlcpy(p, lst->content, BUFFER_SIZE + 1);
		lst = lst->next;
	}
	ft_lstclear(plst, free);
	return (p0);
}

static int	add_to_list(t_list **plst, const char *s, size_t start, size_t len)
{
	char	*sub;
	t_list	*new;

	sub = ft_substr(s, start, len);
	new = ft_lstnew(sub);
	if (!sub || !new)
	{
		free(sub);
		free(new);
		ft_lstclear(plst, free);
		return (-1);
	}
	ft_lstadd_back(plst, new);
	return (0);
}

static ssize_t	read_first(int fd, t_list **plst, char *dst, char **ppos_nl)
{
	size_t	m;
	ssize_t	n;

	if (*plst)
	{
		m = ft_strlcpy(dst, (*plst)->content, BUFFER_SIZE);
		ft_lstclear(plst, free);
	}
	else
		m = 0;
	n = read(fd, dst + m, BUFFER_SIZE - m);
	if (n != -1)
	{
		n += m;
		dst[n] = '\0';
		*ppos_nl = ft_strchr(dst, '\n');
	}
	return (n);
}

char	*get_next_line(int fd)
{
	ssize_t			n;
	static t_list	*listed_lines[MAX_FILES];
	char			*pos_nl;
	char			*line;
	char			buffer[BUFFER_SIZE + 1];

	n = read_first(fd, &listed_lines[fd], buffer, &pos_nl);
	while (n > 0 && !pos_nl)
	{
		n = add_to_list(&listed_lines[fd], buffer, 0, BUFFER_SIZE);
		if (n == -1)
			break;
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = '\0';
		pos_nl = ft_strchr(buffer, '\n');
	}
	if (n != -1 && pos_nl)
		n = add_to_list(&listed_lines[fd], buffer, 0, pos_nl - buffer + 1);
	if (n != -1)
		line = construct_line(&listed_lines[fd]);
	if (n != -1 && pos_nl && *++pos_nl)
		n = add_to_list(&listed_lines[fd], buffer, pos_nl - buffer, BUFFER_SIZE);
	if (n != -1)
		return (line);
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (NULL);
	return ((char *)s);
}
