/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:14:46 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/30 19:33:22 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstadd_back(t_list **plst, t_list *new)
{
	if (*plst)
	{
		while ((*plst)->next)
			*plst = (*plst)->next;
		(*plst)->next = new;
	}
	else
		*plst = new;
}

void	ft_lstclear(t_list **plst, void (*del)(void *))
{
	t_list	*nxt;

	while (*plst)
	{
		nxt = (*plst)->next;
		del((*plst)->content);
		free(*plst);
		*plst = nxt;
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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char *const	src0 = src;

	while (size > 1 && *src)
	{
		*dst++ = *src++;
		size--;
	}
	if (size)
		*dst = '\0';
	while (*src)
		src++;
	return (src - src0);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*p;

	size = ft_strlcpy(NULL, s, 0);
	if (start > size)
	{
		p = malloc(1);
		if (p)
			*p = '\0';
		return (p);
	}
	size -= start;
	if (len < size)
		size = len;
	p = malloc(++size);
	if (p)
		ft_strlcpy(p, s + start, size);
	return (p);
}
