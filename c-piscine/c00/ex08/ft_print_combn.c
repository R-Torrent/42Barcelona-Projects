/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 22:44:40 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/01 23:33:40 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*calc(char *comb, int n)
{
	int	i;

	i = n - 1;
	while (i >= 0)
	{
		if (comb[i] < '9' - n + i + 1)
		{
			comb[i]++;
			while (++i < n)
				comb[i] = comb[i - 1] + 1;
			return (comb);
		}
		i--;
	}
	return (NULL);
}

void	ft_print_combn(int n)
{
	char	comb[9];
	int		i;

	i = 0;
	while (i < n)
	{
		comb[i] = '0' + i;
		i++;
	}
	while (1)
	{
		write(1, comb, n);
		if (calc(comb, n))
			write(1, ", ", 2);
		else
			break ;
	}
}
