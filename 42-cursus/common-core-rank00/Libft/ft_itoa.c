/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:33:27 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/03 19:57:06 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	place_digit(int n, char *str)
{
	int	div;

	div = n / 10;
	if (div)
		place_digit(div, str + 1);
	*str = '0' + n % 10;
}

char	*ft_itoa(int n)
{
	int		n1;
	int		i;
	char	*p;

	n1 = n;
	if (n <= 0)
		i = 1;
	else
		i = 0;
	while (n1)
	{
		n1 /= 10;
		i++;
	}
	p = malloc(sizeof (char) * i);
	if (n < 0)
	{
		*p = '-';
		place_digit(n, p + 1);
	}
	else
		place_digit(n, p);
	return (p);
}
