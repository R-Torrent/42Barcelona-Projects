/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaorozco <jaorozco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 22:17:19 by jaorozco          #+#    #+#             */
/*   Updated: 2023/04/16 22:43:58 by jaorozco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	ft_atou(char *str)
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
	return (-1);
}
