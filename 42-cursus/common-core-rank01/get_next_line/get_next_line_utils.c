/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:14:46 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/28 21:05:28 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstadd_front(t_list **plst, t_list *new)
{
	new->next = *plst;
	*plst = new;
}

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
