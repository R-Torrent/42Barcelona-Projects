/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 20:42:52 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/02 20:56:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	printc(int *comb)
{
	char	w[5];

	w[0] = '0' + comb[0] / 10;
	w[1] = '0' + comb[0] % 10;
	w[2] = ' ';
	w[3] = '0' + comb[1] / 10;
	w[4] = '0' + comb[1] % 10;
	write(1, w, 5);
}

int	*calc(int *comb)
{
	int	i;

	i = 1;
	while (i >= 0)
	{
		if (comb[i] < 98 + i)
		{
			comb[i]++;
			if (i == 0)
				comb[1] = comb[0] + 1;
			return (comb);
		}
		i--;
	}
	return (NULL);
}

void	ft_print_comb2(void)
{
	int	comb[2];

	comb[0] = 0;
	comb[1] = 1;
	while (1)
	{
		printc(comb);
		if (calc(comb))
			write(1, ", ", 2);
		else
			break ;
	}
}
