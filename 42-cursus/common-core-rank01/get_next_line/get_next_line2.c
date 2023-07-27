/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/27 21:29:05 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

typedef struct s_block
{
	char	*str;
	size_t	start;
	size_t	len;
}	*t_pblock;

static void	del_block(void *content)
{
	free(((t_pblock)content)->str);
	free(content);
}

static bool	construct_line(t_list **plst, char **ln, size_t size)
{
	t_list	*lst;

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
		*ln += size;
		**ln = '\0';
		lst = *plst;
		while (lst)
		{
			size = ((t_pblock)lst->content)->len;
			*ln = ft_memcpy(*ln - size, ((t_pblock)lst->content)->str
				+ ((t_pblock)lst->content)->start, size);
			lst = lst->next;
		}
		ft_lstclear(plst, del_block);
	}
	return (*ln);
}

static bool	add_block(t_list **plst, const char *str, size_t len)
{
	char *const		new_substr = ft_substr(str, 0, len);
	t_pblock const	new_blck = malloc(sizeof(struct s_block));
	t_list *const	new_link = ft_lstnew(new_blck);

	if (!new_substr || !new_blck || !new_link)
	{
		free(new_substr);
		free(new_blck);
		free(new_link);
		return (false);
	}
	new_blck->str = new_substr;
	new_blck->start = 0;
	new_blck->len = len;
	new_link->next = *plst;
	*plst = new_link;
	return (true);
}

static bool	read_blocks(int fd, t_list **plst, char *buffer, char **line)
{
	char	*p_nl;
	ssize_t	n;
	size_t	m;

	p_nl = NULL;
	if (*plst)
		p_nl = ft_strchr(((t_pblock)(*plst)->content)->str
			+ ((t_pblock)(*plst)->content)->start, '\n');
	while (!p_nl)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == 0)
			return (construct_line(plst, line, 0));
		if (n == -1 || !add_block(plst, buffer, n))
			return (false);
		p_nl = ft_strchr(((t_pblock)(*plst)->content)->str
			+ ((t_pblock)(*plst)->content)->start, '\n');
	}
	m =  ++p_nl - ((t_pblock)(*plst)->content)->str;
	n = ((t_pblock)(*plst)->content)->len - m;
	if (n == 0)
		return (construct_line(plst, line, 0));
	if (!construct_line(&((*plst)->next), line, m))
		return (false);
	((t_pblock)(*plst)->content)->start = m;
	((t_pblock)(*plst)->content)->len = n;
	ft_memcpy(*line, ((t_pblock)(*plst)->content)->str, m);
	return (true);
}

char	*get_next_line(int fd)
{
	static t_list	*listed_lines[MAX_FILES];
	char			buffer[BUFFER_SIZE + 1];
	char			*line;

	buffer[BUFFER_SIZE] = '\0';
	line = NULL;
	if (!read_blocks(fd, &listed_lines[fd], buffer, &line))
		ft_lstclear(&listed_lines[fd], del_block);
	return (line);
}
