/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/08/01 18:19:58 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

typedef struct s_block
{
	char	*str;
	size_t	len;
}	*t_pblock;

static void	del_block(void *content)
{
	free(((t_pblock)content)->str + ((t_pblock)content)->len - BUFFER_SIZE);
	free(content);
}

static bool	asm_line(t_list **plst, char **ln, size_t size, char *last)
{
	const size_t	len_last = size;
	t_list			*lst;

	lst = *plst;
	while (lst)
	{
		size += ((t_pblock)lst->content)->len;
		lst = lst->next;
	}
	if (size)
		*ln = malloc(size + 1);
	if (*ln)
	{
		(*ln)[size] = '\0';
		*ln = ft_memcpy(*ln + size - len_last, last, len_last);
		lst = *plst;
		while (lst)
		{
			size = ((t_pblock)lst->content)->len;
			*ln = ft_memcpy(*ln - size, ((t_pblock)lst->content)->str, size);
			lst = lst->next;
		}
		ft_lstclear(plst, del_block);
	}
	return (*ln);
}

static bool	add_block(t_list **plst, char *buffer, size_t len)
{
	char *const		text = malloc(BUFFER_SIZE + 1);
	t_pblock const	new_blck = malloc(sizeof(struct s_block));
	t_list *const	new_link = ft_lstnew(new_blck);

	if (!text || !new_blck || !new_link)
	{
		free(text);
		free(new_blck);
		free(new_link);
		return (false);
	}
	buffer[len] = '\0';
	new_blck->str = ft_memcpy(text + BUFFER_SIZE - len, buffer, len + 1);
	new_blck->len = len;
	ft_lstadd_front(plst, new_link);
	return (true);
}

static bool	read_blocks(int fd, t_list **plst, char *buffer, char **line)
{
	char	*p_nl;
	ssize_t	n;

	p_nl = NULL;
	if (*plst)
		p_nl = ft_strchr(((t_pblock)(*plst)->content)->str, '\n');
	while (!p_nl)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == 0)
			return (asm_line(plst, line, 0, NULL));
		if (n == -1 || !add_block(plst, buffer, n))
			return (false);
		p_nl = ft_strchr(((t_pblock)(*plst)->content)->str, '\n');
	}
	n = ++p_nl - ((t_pblock)(*plst)->content)->str;
	if (!asm_line(&((*plst)->next), line, n, ((t_pblock)(*plst)->content)->str))
		return (false);
	((t_pblock)(*plst)->content)->str = p_nl;
	((t_pblock)(*plst)->content)->len -= n;
	return (((t_pblock)(*plst)->content)->len);
}

char	*get_next_line(int fd)
{
	static t_list	*listed_lines[MAX_FILES];
	char			buffer[BUFFER_SIZE + 1];
	char			*line;

	line = NULL;
	if (!read_blocks(fd, &listed_lines[fd], buffer, &line))
		ft_lstclear(&listed_lines[fd], del_block);
	return (line);
}
