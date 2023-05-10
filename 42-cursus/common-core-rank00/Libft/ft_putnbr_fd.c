/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 08:03:08 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/10 11:53:57 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putdgts_fd(int n, int fd)
{
	int	x;

	x = n / 10;
	if (x)
		ft_putdgts_fd(x, fd);
	if (n < 0)
		x = '0' - n % 10;
	else
		x = '0' + n % 10;
	ft_putchar_fd(x, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putdgts_fd(n, fd);
}
