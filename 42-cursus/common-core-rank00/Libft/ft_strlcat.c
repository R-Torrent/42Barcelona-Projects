/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:16:42 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/07 19:19:19 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*dst0;

	dst0 = dst;
	while (size && *dst)
	{
		dst++;
		size--;
	}
	return (dst - dst0 + ft_strlcpy(dst, src, size));
}
