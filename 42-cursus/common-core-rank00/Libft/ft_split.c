/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:51:41 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/09 03:06:14 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	counter(const char *s, char c, const char **index)
{
	size_t	nc;
	bool	count;

	nc = 0;
	count = true;
	while (*s)
	{
		if (*s != c)
		{
			if (count)
			{
				nc++;
				if (index)
					*index++ = s;
			}
			count = false;
		}
		else
			count = true;
		s++;
	}
	if (index)
		*index = NULL;
	return (nc);
}

char	**ft_split(const char *s, char c)
{
	const char	**p;
	
	p = malloc(sizeof (char *) * counter(s, c, NULL) + 1);
	counter(s, c, p);
	return ((char **)p);
}
