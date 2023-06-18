/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:03:47 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/18 13:33:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	n;
	int	sign;

	while (ft_isspace(*str))
		str++;
	sign = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	n = 0;
	while (ft_isdigit(*str))
	{
		n *= 10;
		if (sign)
			n -= *str - '0';
		else
			n += *str - '0';
		str++;
	}
	return (n);
}
