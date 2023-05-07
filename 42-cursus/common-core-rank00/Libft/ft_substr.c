/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:43:27 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/07 14:15:40 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*dst;

	size = ft_strlen(s);
	if (start > size)
		return (NULL);
	size -= start;
	if (len < size)
		size = len;
	dst = malloc(++size);
	if (dst)
		ft_strlcpy(dst, s + start, size);
	return (dst);
}
