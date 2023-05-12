/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:51:41 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/13 00:47:37 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	count(const char *s, char c, size_t *nc, size_t *nw)
{
	bool	neww;

	*nc = 0;
	*nw = 0;
	neww = true;
	while (*s)
	{
		if (*s != c)
		{
			(*nc)++;
			if (neww)
				(*nw)++;
			neww = false;
		}
		else
			neww = true;
		s++;
	}
}

static void	find_entries(const char *s, char c, char **index)
{
	bool	neww;

	neww = true;
	while (*s)
	{
		if (*s != c)
		{
			if (neww)
				*index++ = (char *)s;
			neww = false;
		}
		else
			neww = true;
		s++;
	}
	*index = NULL;
}

static size_t	copy_entries(char *dst, const char *src, char c, char **index)
{
	const char *const	dst0 = dst;

	*index = dst;
	while (*src && *src != c)
		*dst++ = *src++;
	*dst++ = '\0';
	return (dst - dst0);
}

char	**ft_split(const char *s, char c)
{
	size_t	nc;
	size_t	nw;
	size_t	size_index;
	char	**p;
	char	**p1;

	count(s, c, &nc, &nw);
	size_index = sizeof (char *) * (nw + 1);
	p = malloc(size_index + nc + nw);
	if (p)
	{
		find_entries(s, c, p);
		nc = size_index;
		p1 = p;
		while (*p1)
		{
			nc += copy_entries((char *)p + nc, *p1, c, p1);
			p1++;
		}
	}
	return (p);
}
