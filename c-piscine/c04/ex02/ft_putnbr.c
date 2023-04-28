/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:09:26 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/01 22:39:32 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	rec_print(unsigned int u)
{
	unsigned int	div;

	div = u / 10;
	if (div)
		rec_print(div);
	div = '0' + u % 10;
	write(1, &div, 1);
}

void	ft_putnbr(int nb)
{
	unsigned int	nbu;

	if (nb < 0)
	{
		write(1, "-", 1);
		nbu = -nb;
	}
	else
		nbu = nb;
	rec_print(nbu);
}
