/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubert- <jaubert-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 20:24:33 by jaubert-          #+#    #+#             */
/*   Updated: 2023/04/16 23:47:47 by jaubert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	dictionary_fill(char *file, t_entry **dictionary, int *dict_size)
{
	char			*text;
	t_array_pchar	index_str;
	int				result;
	int				i;

	result = dictionary_init(file, &text, &index_str);
	if (result != SUCCESS)
		return (result);
	*dictionary = malloc(sizeof(t_entry) * index_str.length);
	if (!*dictionary)
	{
		free(text);
		free(index_str.array);
		return (MMRY_ERROR);
	}
	*dict_size = index_str.length;
	i = 0;
	while (i < index_str.length)
	{
		(*dictionary)[i].key = ft_atoi(index_str.array[i]);
		(*dictionary)[i].value = ft_strip(index_str.array[i]);
		i++;
	}	
	return (SUCCESS);
}
