/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:47:54 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/07 11:43:18 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(int c)
{
	return ('a' <= c && c <= 'z');
}

int	ft_toupper(int c)
{
	if (ft_islower(c))
		c &= ~0x20;
	return (c);
}
