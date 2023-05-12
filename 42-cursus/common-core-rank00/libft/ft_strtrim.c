/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:55:49 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/13 00:53:50 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	in_set(const char *set, const char c)
{
	while (*set)
		if (*set++ == c)
			return (true);
	return (false);
}

char	*ft_strtrim(const char *s, const char *set)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	while (in_set(set, s[i]))
		i++;
	if (!s[i])
		p = ft_calloc(1, 1);
	else
	{
		j = ft_strlen(s) - 1;
		while (i < j && in_set(set, s[j]))
			j--;
		p = ft_substr(s, i, j - i + 1);
	}
	return (p);
}
