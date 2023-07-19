/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/19 12:25:34 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

struct s_block
{
	char	*str;
	size_t	len;
};

static void	del_block(void *content)
{
	struct s_block *const	block = content;

	free(block->str);
	free(block);
}

static char	*construct_line(t_list **plst)
{
	t_list			*lst;
	size_t			size;
	struct s_block	*block;
	char			*p;

	lst = *plst;
	size = 0;
	while (lst)
	{
		block = lst->content;
		size += block->len;
		lst = lst->next;
	}
	lst = *plst;
	p = malloc(size + 1);
	if (!lst || !p)
		return (NULL);
	p += size;
	*p = '\0';
	while (lst)
	{
		block = lst->content;
		p -= block->len;
		ft_memcpy(p, block->str, block->len);
		lst = lst->next;
	}
	ft_lstclear(plst, del_block);
	return (p);
}

static ssize_t	add_block(t_list **plst, const char *str, size_t i0, size_t len)
{
	struct s_block	*new_block;	
	char			*new_substr;
	t_list			*new_link;

	new_block = malloc(sizeof(struct s_block));
	new_substr = ft_substr(str, i0, len);
	new_link = ft_lstnew(new_block);
	if (!new_block || !new_substr || !new_link)
	{
		free(new_block);
		free(new_substr);
		free(new_link);
		ft_lstclear(plst, del_block);
		return (-1);
	}
	new_block->str = new_substr;
	new_block->len = len;
	new_link->next = *plst;
	*plst = new_link;
	return (len);
}

static ssize_t	read_first(int fd, t_list **plst, char *dst, char **ppos_nl)
{
	struct s_block	*block;
	ssize_t			n;

	if (*plst)
	{
		block = (*plst)->content;
		n = block->len;
		ft_memcpy(dst, block->str, n);
		ft_lstclear(plst, del_block);
	}
	else
		n = read(fd, dst, BUFFER_SIZE);
	if (n != -1)
	{
		dst[n] = '\0';
		*ppos_nl = ft_strchr(dst, '\n');
	}
	return (n);
}

char	*get_next_line(int fd)
{
	ssize_t			n;
	static t_list	*listed_lines[MAX_FILES];
	char			*pos_nl;
	char			*line;
	char			buf[BUFFER_SIZE + 1];

	n = read_first(fd, &listed_lines[fd], buf, &pos_nl);
	while (n > 0 && !pos_nl)
	{
		n = add_block(&listed_lines[fd], buf, 0, n);
		if (n == -1)
			break ;
		n = read(fd, buf, BUFFER_SIZE);
		buf[n] = '\0';
		pos_nl = ft_strchr(buf, '\n');
	}
	if (n != -1 && pos_nl)
		n = add_block(&listed_lines[fd], buf, 0, pos_nl - buf + 1);
	if (n != -1)
		line = construct_line(&listed_lines[fd]);
	if (n != -1 && pos_nl && *++pos_nl)
		n = add_block(&listed_lines[fd], buf, pos_nl - buf, BUFFER_SIZE - n);
	if (n != -1)
		return (line);
	return (NULL);
}
