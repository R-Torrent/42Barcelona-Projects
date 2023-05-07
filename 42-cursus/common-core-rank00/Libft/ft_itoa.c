/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:33:27 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/07 19:25:56 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	place_digit(int n, char **str)
{
	int	div;

	div = n / 10;
	if (div)
		place_digit(div, str);
	*(*str)++ = '0' + n % 10;
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
	int		nc;
	char	*p0;
	char	*p;

	nc = count_chars(n);
	p0 = malloc(nc + 1);
	if (p0)
	{
		p = p0;
		if (n < 0)
			*p++ = '-';
		place_digit(n, &p);
		*(p0 + nc) = '\0';
	}
	return (p0);
}
