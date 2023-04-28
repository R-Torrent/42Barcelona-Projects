/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_entries.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:42:05 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/16 19:06:20 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

struct s_pair
{
	int	current;
	int	target;
};

static void	append_char(char *str, char c)
{
	while (*str)
		str++;
	*str++ = c;
	*str = '\0';
}

static void	check_n_copy(char *dst, char *src, bool *prev_nl,
		struct s_pair *p_indices)
{
	while (*src)
	{
		if (*src == '\n')
		{
			if (!*prev_nl)
				p_indices->current++;
			*prev_nl = true;
		}
		else
		{
			if (p_indices->current == p_indices->target)
				append_char(dst, *src);
			*prev_nl = false;
		}
		src++;
	}
}

static int	read_n_copy_text(char *file, char *dest, int target_entry)
{
	int				fd;
	int				nc;
	struct s_pair	indices;
	char			buff[BUF_SIZE + 1];
	bool			prev_nl;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FILE_ERROR);
	indices.current = 0;
	indices.target = target_entry;
	prev_nl = true;
	nc = read(fd, buff, BUF_SIZE);
	while (nc)
	{
		buff[nc] = '\0';
		check_n_copy(dest, buff, &prev_nl, &indices);
		if (indices.current > indices.target)
			break ;
		nc = read(fd, buff, BUF_SIZE);
	}
	if (close(fd) == -1)
		return (FILE_ERROR);
	return (SUCCESS);
}	

static int	mem_alloc(char **p_text, t_array_pchar *p_strs_table,
		int num_entries, int num_chars)
{
	*p_text = malloc(sizeof(char) * (num_chars + num_entries));
	if (!*p_text)
		return (MMRY_ERROR);
	p_strs_table->array = malloc(sizeof(char *) * num_entries);
	if (!p_strs_table->array)
		return (MMRY_ERROR);
	return (SUCCESS);
}

int	dictionary_entries(char *file, t_array_int nchars_table, char **p_text,
		t_array_pchar *p_strs_table)
{
	char	*text_current;
	int		total_nc;
	int		i;
	int		result;

	total_nc = 0;
	i = 0;
	while (i < nchars_table.length)
		total_nc += nchars_table.array[i++];
	result = mem_alloc(p_text, p_strs_table, nchars_table.length, total_nc);
	if (result != SUCCESS)
		return (result);
	i = 0;
	text_current = *p_text;
	while (i < nchars_table.length)
	{
		p_strs_table->array[i] = text_current;
		*p_strs_table->array[i] = '\0';
		result = read_n_copy_text(file, text_current, i);
		if (result != SUCCESS)
			return (result);
		text_current += nchars_table.array[i++] + 1;
	}
	return (SUCCESS);
}
