/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:14:46 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/20 17:08:10 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (NULL);
	return ((char *)s);
}

char	*ft_strdup(const char *s)
{
	size_t	strlen;
	char	*p;

	p = s;
	while (*p)
		p++;
	strlen = p - s;
	p = malloc(strlen + 1);
	if (p)
	{
		while (*s)
			*p++ = *s++;
		*p = '\0';
	}
	return (p);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*p;

	size = ft_strlen(s);
	if (start > size)
		return (ft_calloc(1, 1));
	size -= start;
	if (len < size)
		size = len;
	p = malloc(++size);
	if (p)
		ft_strlcpy(p, s + start, size);
	return (p);
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
