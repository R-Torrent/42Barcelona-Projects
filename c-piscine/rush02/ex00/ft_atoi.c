/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubert- <jaubert-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:25:35 by jaubert-          #+#    #+#             */
/*   Updated: 2023/04/15 19:42:04 by jaubert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	ft_atoi(char *str)
{
	int	i;
	int	j;
	int	resultat;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
			i++;
	if (i != 0)
	{
		j = 0;
		resultat = 0;
		while (j < i)
		{
			resultat = (str[j] - '0') + (resultat * 10);
			j++;
		}
		return (resultat);
	}
	return (0);
}
