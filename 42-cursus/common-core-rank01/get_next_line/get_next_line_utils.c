/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:14:46 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/23 06:23:34 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstclear(t_list **plst, void (*del)(void *))
{
	t_list	*next;

	while (*plst)
	{
		next = (*plst)->next;
		del((*plst)->content);
		free(*plst);
		*plst = next;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list *const	p = malloc(sizeof (t_list));

	if (p)
	{
		p->content = content;
		p->next = NULL;
	}
	return (p);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*udst;
	const unsigned char	*usrc;

	udst = dst;
	usrc = src;
	while (n--)
		*udst++ = *usrc++;
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (NULL);
	return ((char *)s);
}

// NOTE: This toned down version of 'ft_substr' is intended to be used solely in
// this file, in conjunction with 'get_next_line.c'.

char	*ft_substr(const char *s, size_t start, size_t len)
{
	size_t	size;
	char	*p;

	(void)start;
	size = ft_strchr(s, '\0') - s;
	if (len < size)
		size = len;
	p = malloc(size + 1);
	if (p)
	{
		ft_memcpy(p, s, size);
		p[size] = '\0';
	}
	return (p);
}
