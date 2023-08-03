/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/08/03 14:38:52 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

typedef struct s_block
{
	char			*start;
	size_t			len;
	unsigned int	index;
	struct s_block	*prev;
	char			str[BUFFER_SIZE];
}	*t_blocks;

static void	clear_blocks(t_blocks *plist, bool skip_first)
{
	t_blocks	prev;

	while (*plist)
	{
		prev = (*plist)->prev;
		if (!(*plist)->index || !prev)
		{
			if (!skip_first)
				free(*plist - (*plist)->index);
			else
				skip_first = false;
		}
		*plist = prev;
	}
}

static bool	asm_line(t_blocks *plist, char **line, size_t size, char *last)
{
	const size_t	len_last = size;
	t_blocks		blocks;

	blocks = *plist;
	while (blocks)
	{
		size += blocks->len;
		blocks = blocks->prev;
	}
	if (size)
		*line = malloc(size + 1);
	if (*line)
	{
		(*line)[size] = '\0';
		*line = ft_memcpy(*line + size - len_last, last, len_last);
		blocks = *plist;
		while (blocks)
		{
			size = blocks->len;
			*line = ft_memcpy(*line - size, blocks->start, size);
			blocks = blocks->prev;
		}
		clear_blocks(plist, len_last);
	}
	return (*line);
}

static ssize_t	add_block(int fd, t_blocks *plist)
{
	const bool	new_batch = !*plist || (*plist)->index == DEFAULT_LIST_SIZE - 1;
	t_blocks	new_block;
	ssize_t		n;

	if (new_batch)
		new_block = malloc(sizeof(struct s_block) * DEFAULT_LIST_SIZE);
	else
		new_block = (*plist) + 1;
	if (!new_block)
		return (-1);
	n = read(fd, new_block->str, BUFFER_SIZE);
	if (n > 0)
	{
		new_block->start = new_block->str;
		new_block->len = n;
		if (new_batch)
			new_block->index = 0;
		else
			new_block->index = (*plist)->index + 1;
		new_block->prev = *plist;
		*plist = new_block;
	}
	else if (new_batch)
		free(new_block);
	return (n);
}

static bool	read_blocks(int fd, t_blocks *plist, char **line)
{
	char	*p_nl;
	ssize_t	n;

	p_nl = NULL;
	if (*plist)
		p_nl = ft_memchr((*plist)->start, '\n', (*plist)->len);
	while (!p_nl)
	{
		n = add_block(fd, plist);
		if (n < 0)
			return (false);
		if (n == 0)
			return (asm_line(plist, line, 0, NULL));
		p_nl = ft_memchr((*plist)->start, '\n', (*plist)->len);
	}
	n = ++p_nl - (*plist)->start;
	if (!asm_line(&(*plist)->prev, line, n, (*plist)->start))
		return (false);
	(*plist)->start = p_nl;
	(*plist)->len -= n;
	return ((*plist)->len);
}

char	*get_next_line(int fd)
{
	static t_blocks	listed_lines[MAX_FILES];
	char			*line;

	line = NULL;
	if (fd >= 0 && fd < MAX_FILES && BUFFER_SIZE > 0 && DEFAULT_LIST_SIZE > 0
		&& !read_blocks(fd, &listed_lines[fd], &line))
		clear_blocks(&listed_lines[fd], false);
	return (line);
}
