/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 13:27:41 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/16 23:28:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

// Frees allocated memory
static void	free_memory(t_array_int nchars_table, char **text,
		t_array_pchar *index)
{
	free(nchars_table.array);
	free(*text);
	free(index->array);
}

// Stores raw text into the address pointed by 'text' and creates the entry
// 'index'.
int	dictionary_init(char *file, char **text, t_array_pchar *index)
{
	t_array_int	nchars_table;
	int			result;

	*text = NULL;
	index->array = NULL;
	nchars_table.array = NULL;
	result = dictionary_entry_sizes(file, &nchars_table);
	if (result != SUCCESS)
	{
		free_memory(nchars_table, text, index);
		return (result);
	}
	index->length = nchars_table.length;
	result = dictionary_entries(file, nchars_table, text, index);
	if (result != SUCCESS)
		free_memory(nchars_table, text, index);
	return (result);
}
