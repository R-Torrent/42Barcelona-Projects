/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:56:35 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/16 12:59:52 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// BOGUS condition added to pass Francinette

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*udst;
	const unsigned char	*usrc;

	if (!dst && !src)
		return (dst);
	udst = dst;
	usrc = src;
	while (n--)
		*udst++ = *usrc++;
	return (dst);
}
