/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:49:14 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/06 00:37:12 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*udst;
	const unsigned char	*usrc;

	udst = dst;
	usrc = src;
	if (usrc < udst && udst < usrc + n)
	{
		udst += n;
		usrc += n;
		while (n--)
			*--udst = *--usrc;
	}
	else
		while (n--)
			*udst++ = *usrc++;
	return (dst);
}
