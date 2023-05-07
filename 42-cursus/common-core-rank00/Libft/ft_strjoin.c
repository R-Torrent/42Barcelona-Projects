/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:27:07 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/07 14:37:05 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	size;
	char	*dst;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(size);
	if (dst)
	{
		ft_strlcpy(dst, s1, size);
		ft_strlcat(dst, s2, size);
	}
	return (dst);
}
