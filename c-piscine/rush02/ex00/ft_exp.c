/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubert- <jaubert-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:51:10 by jaubert-          #+#    #+#             */
/*   Updated: 2023/04/16 20:19:57 by jaubert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	ft_exp(int base, int exp)
{
	int	i;
	int	result;

	if (exp == 0)
		return (1);
	i = 1;
	result = base;
	while (i < exp)
	{
		result = result * base;
		i++;
	}
	return (result);
}
