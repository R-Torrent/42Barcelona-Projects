/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:55:49 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/17 19:55:35 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s, const char *set)
{
	const char	*t;
	char		*p;

	while (*s && ft_strchr(set, *s))
		s++;
	if (!*s)
		p = ft_calloc(1, 1);
	else
	{
		t = s + ft_strlen(s) - 1;
		while (s < t && ft_strchr(set, *t))
			t--;
		p = ft_substr(s, 0, t - s + 1);
	}
	return (p);
}
