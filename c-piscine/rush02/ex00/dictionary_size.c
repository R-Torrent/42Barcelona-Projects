/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:52:32 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/16 13:57:58 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

// Returns number of non-empty newlines found in the string
static int	number_newlines(char *str, bool *prev_nl)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str++ == '\n')
		{
			if (!*prev_nl)
				count++;
			*prev_nl = true;
		}
		else
			*prev_nl = false;
	}
	return (count);
}

// Fills nchars_tables with numbers of characters
static void	number_chars_in_line(char *str, bool *prev_nl,
		t_array_int *p_nchars_table)
{
	while (*str)
	{
		if (*prev_nl)
			*p_nchars_table->array = 0;
		if (*str++ == '\n')
		{
			if (!*prev_nl)
				(p_nchars_table->array)++;
			*prev_nl = true;
		}
		else
		{
			(*p_nchars_table->array)++;
			*prev_nl = false;
		}
	}
}

// Returns number of entries in the dictionary; -1 if error
static int	determine_size_dictionary(char *file)
{
	int		fd;
	int		nc;
	int		nl;
	char	buff[BUF_SIZE + 1];
	bool	prev_nl;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	nl = 0;
	prev_nl = true;
	nc = read(fd, buff, BUF_SIZE);
	while (nc)
	{
		buff[nc] = '\0';
		nl += number_newlines(buff, &prev_nl);
		nc = read(fd, buff, BUF_SIZE);
	}
	if (close(fd) == -1)
		return (-1);
	return (nl);
}

// Fill nchars_table by calling number_characters_in_line function
static int	determine_raw_line_sizes(char *file, t_array_int *p_nchars_table)
{
	int		fd;
	int		nc;
	char	buff[BUF_SIZE + 1];
	bool	prev_nl;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FILE_ERROR);
	prev_nl = true;
	nc = read(fd, buff, BUF_SIZE);
	while (nc)
	{
		buff[nc] = '\0';
		number_chars_in_line(buff, &prev_nl, p_nchars_table);
		nc = read(fd, buff, BUF_SIZE);
	}
	if (close(fd) == -1)
		return (FILE_ERROR);
	return (SUCCESS);
}

int	dictionary_entry_sizes(char *file, t_array_int *p_nchars_table)
{
	int		*p0;
	int		result;

	p_nchars_table->length = determine_size_dictionary(file);
	if (p_nchars_table->length == -1)
		return (FILE_ERROR);
	p_nchars_table->array = malloc(sizeof(int) * p_nchars_table->length);
	if (!p_nchars_table->array)
		return (MMRY_ERROR);
	p0 = p_nchars_table->array;
	result = determine_raw_line_sizes(file, p_nchars_table);
	p_nchars_table->array = p0;
	return (result);
}
