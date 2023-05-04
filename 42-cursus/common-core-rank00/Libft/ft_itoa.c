/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:33:27 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/04 17:40:57 by rtorrent         ###   ########.fr       */
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

static int	count_chars(int n)
{
	int	count;

	if (n <= 0)
		count = 1;
	else
		count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*p;

	i = count_chars(n);
	p = malloc(sizeof (char) * i);
	if (p)
	{
		if (n < 0)
		{
			*p = '-';
			place_digit(n, p + 1);
		}
		else
			place_digit(n, p);
		*(p + i) = '\0';
	}
	return (p);
}
