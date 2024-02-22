/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:51:41 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/16 13:09:25 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_strs(const char *s, char c)
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
				nw++;
			neww = false;
		}
		else
			neww = true;
		s++;
	}
	return (nw);
}

static void	copy_strs(const char *s, char c, char **p)
{
	const char	*sw;
	bool		neww;

	neww = true;
	while (*s)
	{
		if (*s != c)
		{
			if (neww)
				sw = s;
			neww = false;
		}
		else if (!neww)
		{
			neww = true;
			*p++ = ft_substr(sw, 0, s - sw);
		}
		s++;
	}
	if (!neww)
		*p++ = ft_substr(sw, 0, s - sw);
	*p = NULL;
}

static void	check_strs(char ***pp, size_t nw)
{
	char	**p1;

	p1 = *pp;
	while (*p1)
		p1++;
	if (p1 - *pp < (ptrdiff_t)nw)
	{
		p1 = *pp;
		while (nw--)
			free(*p1++);
		free(*pp);
		*pp = NULL;
	}
}

char	**ft_split(const char *s, char c)
{
	const size_t	nw = count_strs(s, c);
	char			**p;

	p = malloc(sizeof (char *) * (nw + 1));
	if (p)
	{
		copy_strs(s, c, p);
		check_strs(&p, nw);
	}
	return (p);
}
