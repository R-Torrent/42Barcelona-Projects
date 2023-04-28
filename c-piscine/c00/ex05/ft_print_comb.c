/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 11:42:03 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/01 22:03:22 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*calc(char *comb)
{
	int	i;

	i = 2;
	while (i >= 0)
	{
		if (comb[i] < '7' + i)
		{
			comb[i]++;
			while (++i < 3)
				comb[i] = comb[i - 1] + 1;
			return (comb);
		}
		i--;
	}
	return (NULL);
}

void	ft_print_comb(void)
{
	char	comb[3];

	comb[0] = '0';
	comb[1] = '1';
	comb[2] = '2';
	while (1)
	{
		write(1, comb, 3);
		if (calc(comb))
			write(1, ", ", 2);
		else
			break ;
	}
}
