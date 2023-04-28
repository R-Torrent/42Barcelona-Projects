/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_by_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubert- <jaubert-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 11:05:17 by jaubert-          #+#    #+#             */
/*   Updated: 2023/04/16 15:38:46 by jaubert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

char	*ft_find_by_key(int needle, t_entry *dictionary, int dict_len)
{
	int	i;
	int	key;

	i = 0;
	while (i < dict_len)
	{
		key = dictionary[i].key;
		if (key == needle)
			return (dictionary[i].value);
		i++;
	}
	return ("");
}
