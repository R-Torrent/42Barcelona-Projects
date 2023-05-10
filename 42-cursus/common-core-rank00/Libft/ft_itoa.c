/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:33:27 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/10 11:48:32 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	place_digit(int n, char **str)
{
	int	x;

	x = n / 10;
	if (x)
		place_digit(x, str);
	if (n < 0)
		x = '0' - n % 10;
	else
		x = '0' + n % 10;
	*(*str)++ = x;
}

static size_t	count_chars(int n)
{
	size_t	count;

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
	size_t	nc;
	char	*p;
	char	*p1;

	nc = count_chars(n);
	p = malloc(nc + 1);
	if (p)
	{
		p1 = p;
		if (n < 0)
			*p1++ = '-';
		place_digit(n, &p1);
		*(p + nc) = '\0';
	}
	return (p);
}
