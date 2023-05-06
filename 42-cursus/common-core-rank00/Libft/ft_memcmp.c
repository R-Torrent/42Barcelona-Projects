/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:21:22 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/06 01:49:49 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*us1;
	const unsigned char	*us2;

	us1 = s1;
	us2 = s2;
	while (n--)
	{
		if (*us1 != *us2)
			return (*us1 - *us2);
		us1++, us2++;
	}
	return (0);
}
