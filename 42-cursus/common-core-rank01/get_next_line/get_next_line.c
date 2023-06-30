/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/30 10:44:52 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*construct_line(t_list *lst0)
{
	t_list	*lst;
	size_t	size;
	char	*p0;
	char	*p;

	lst = lst0;
	size = 0;
	while (lst)
	{
		size += ft_strlcpy(NULL, lst->content, 0);
		lst = lst->next;
	}
	p0 = malloc(++size);
	p = p0;
	lst = lst0;
	while (p0 && lst)
	{
		p += ft_strlcpy(p, lst->content, BUFFER_SIZE);
		lst = lst->next;
	}
	ft_lstclear(&lst0, free);
	return (p0);
}

static int	add(t_list **plst, const char *s, unsigned int start, size_t len)
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

static int	read_first(int fd, t_list **plst, char *dst)
{
	int	n;

	if (*plst)
	{
		n = ft_strlcpy(dst, (*plst)->content, BUFFER_SIZE);
		ft_lstclear(plst, free);
	}
	else
	{
		n = read(fd, dst, BUFFER_SIZE);
		dst[n] = '\0';
	}
	return (n);
}

char	*get_next_line(int fd)
{
	int				n;
	char			*pos_nl;
	char			buffer[BUFFER_SIZE + 1];
	static t_list	*listed_lines[MAX_FILES];

	n = read_first(fd, &listed_lines[fd], buffer);
	pos_nl = NULL;
	while (n > 0 && !pos_nl)
	{
		pos_nl = ft_strchr(buffer, '\n');
		if (pos_nl)
			n = add(&listed_lines[fd], buffer, 0, pos_nl - buffer + 1);
		else
			n = add(&listed_lines[fd], buffer, 0, BUFFER_SIZE);
		if (n != -1)
			n = read(fd, buffer, BUFFER_SIZE);
	}
	if (n != -1 && pos_nl && (size_t)(pos_nl - buffer)
		< (ft_strlcpy(NULL, buffer, 0) - 1))
		n = add(&listed_lines[fd], buffer, pos_nl - buffer + 1, BUFFER_SIZE);
	if (n == -1 || !listed_lines[fd])
		return (NULL);
	return (construct_line(listed_lines[fd]));
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (NULL);
	return ((char *)s);
}
