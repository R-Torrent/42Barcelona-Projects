/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:27:07 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/14 18:57:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	const size_t	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	char *const		p = malloc(size);

	if (p)
	{
		ft_strlcpy(p, s1, size);
		ft_strlcat(p, s2, size);
	}
	return (p);
}
