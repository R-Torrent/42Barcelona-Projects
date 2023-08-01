/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/08/01 22:01:29 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

typedef struct s_block
{
	char			*start;
	size_t			len;
	struct s_block	*next;
	char			str[BUFFER_SIZE + 1];
}	t_block;

static void	clear_blocks(t_block **pblocks)
{
	t_block	*next;

	while (*pblocks)
	{
		next = (*pblocks)->next;
		free(*pblocks);
		*pblocks = next;
	}
}

static bool	asm_line(t_block **pblocks, char **line, size_t size, char *last)
{
	const size_t	len_last = size;
	t_block			*pblock;

	pblock = *pblocks;
	while (pblock)
	{
		size += pblock->len;
		pblock = pblock->next;
	}
	if (size)
		*line = malloc(size + 1);
	if (*line)
	{
		(*line)[size] = '\0';
		*line = ft_memcpy(*line + size - len_last, last, len_last);
		pblock = *pblocks;
		while (pblock)
		{
			size = pblock->len;
			*line = ft_memcpy(*line - size, pblock->start, size);
			pblock = pblock->next;
		}
		clear_blocks(pblocks);
	}
	return (*line);
}

static ssize_t	add_block(int fd, t_block **pblocks)
{
	t_block *const	new_block = malloc(sizeof(struct s_block));
	ssize_t			n;

	if (!new_block)
		return (-1);
	n = read(fd, new_block->str, BUFFER_SIZE);
	if (n <= 0)
	{
		free(new_block);
		return (n);
	}
	new_block->start = new_block->str;
	new_block->len = n;
	(new_block->str)[n] = '\0';
	new_block->next = *pblocks;
	*pblocks = new_block;
	return (n);
}

static bool	read_blocks(int fd, t_block **pblocks, char **line)
{
	char	*p_nl;
	ssize_t	n;

	p_nl = NULL;
	if (*pblocks)
		p_nl = ft_strchr((*pblocks)->start, '\n');
	while (!p_nl)
	{
		n = add_block(fd, pblocks);
		if (n < 0)
			return (false);
		if (n == 0)
			return (asm_line(pblocks, line, 0, NULL));
		p_nl = ft_strchr((*pblocks)->start, '\n');
	}
	n = ++p_nl - (*pblocks)->start;
	if (!asm_line(&(*pblocks)->next, line, n, (*pblocks)->start))
		return (false);
	(*pblocks)->start = p_nl;
	(*pblocks)->len -= n;
	return ((*pblocks)->len);
}

char	*get_next_line(int fd)
{
	static t_block	*listed_lines[MAX_FILES];
	char			*line;

	line = NULL;
	if (fd < 0 || fd >= MAX_FILES || BUFFER_SIZE <= 0)
		return (line);
	if (!read_blocks(fd, &listed_lines[fd], &line) && fd >= 0)
		clear_blocks(&listed_lines[fd]);
	return (line);
}
