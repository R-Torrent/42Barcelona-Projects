/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:18:01 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/06 20:02:42 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Optimized 'bubble sort' */
void	ft_sort_int_tab(int *tab, int size)
{
	int	swapped;
	int	i;
	int	x;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 1;
		while (i < size)
		{
			if (tab[i - 1] > tab[i])
			{
				x = tab[i - 1];
				tab[i - 1] = tab[i];
				tab[i] = x;
				swapped = 1;
			}
			i++;
		}
		size--;
	}
}
