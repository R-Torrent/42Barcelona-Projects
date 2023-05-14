/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:51:41 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/14 21:28:54 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_strs(const char *s, char c, char **index)
{
	size_t	nw;
	bool	neww;

	nw = 0;
	neww = true;
	while (*s)
	{
		if (*s != c)
		{
			if (neww)
			{
				nw++;
				if (index)
					*index++ = (char *)s;
			}
			neww = false;
		}
		else
			neww = true;
		s++;
	}
	if (index)
		*index = NULL;
	return (nw);
}

static char	*copy_strs(const char *src, char c)
{
	const char *const	src0 = src;

	while (*src && *src != c)
		src++;
	return (ft_substr(src0, 0, src - src0));
}

char	**ft_split(const char *s, char c)
{
	char **const	p = malloc(sizeof (char *) * (find_strs(s, c, NULL) + 1));
	char			**p1;

	if (p)
	{
		find_strs(s, c, p);
		p1 = p;
		while (*p1)
		{
			*p1 = copy_strs(*p1, c);
			if (!*p1)
			{
				p1 = p;
				while (*p1)
					free(p1++);
				free(p);
				break ;
			}
			p1++;
		}
	}
	return (p);
}
