/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/24 02:10:55 by rtorrent         ###   ########.fr       */
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
	free(((t_pblock)content)->str);
	free(content);
}

static void	construct_line(t_list **plst, char **ln)
{
	t_list			*lst;
	size_t			size;

	lst = *plst;
	size = 0;
	while (lst)
	{
		size += ((t_pblock)lst->content)->len;
		lst = lst->next;
	}
	lst = *plst;
	*ln = malloc(size + 1);
	if (*ln)
	{
		*ln += size;
		**ln = '\0';
		while (lst)
		{
			size = ((t_pblock)lst->content)->len;
			*ln = ft_memcpy(*ln - size, ((t_pblock)lst->content)->str, size);
			lst = lst->next;
		}
	}
	ft_lstclear(plst, del_block);
}

static ssize_t	add_block(t_list **plst, const char *str, size_t len, char **ln)
{
	char *const		new_substr = ft_substr(str, 0, len);
	t_pblock const	new_blck = malloc(sizeof(struct s_block));
	t_list *const	new_link = ft_lstnew(new_blck);

	if (!new_substr || !new_blck || !new_link)
	{
		free(new_substr);
		free(new_blck);
		free(new_link);
		ft_lstclear(plst, del_block);
		if (*ln)
		{
			free(*ln);
			*ln = NULL;
		}
		return (-1);
	}
	new_blck->str = new_substr;
	new_blck->len = len;
	new_link->next = *plst;
	*plst = new_link;
	return (len);
}

static ssize_t	read_first(int fd, t_list **plst, char *dst, char **pp_nl)
{
	ssize_t			n;

	if (*plst)
	{
		n = ((t_pblock)(*plst)->content)->len;
		ft_memcpy(dst, ((t_pblock)(*plst)->content)->str, n);
		ft_lstclear(plst, del_block);
	}
	else
		n = read(fd, dst, BUFFER_SIZE);
	if (n != -1)
	{
		dst[n] = '\0';
		*pp_nl = ft_strchr(dst, '\n');
	}
	return (n);
}

char	*get_next_line(int fd)
{
	ssize_t			n;
	static t_list	*listed_lns[MAX_FILES];
	char			buffer[BUFFER_SIZE + 1];
	char			*p_nl;
	char			*ln;

	n = read_first(fd, &listed_lns[fd], buffer, &p_nl);
	ln = NULL;
	while (n > 0 && !p_nl)
	{
		n = add_block(&listed_lns[fd], buffer, n, &ln);
		if (n != -1)
			n = read(fd, buffer, BUFFER_SIZE);
		if (n != -1)
			buffer[n] = '\0';
		if (n != -1)
			p_nl = ft_strchr(buffer, '\n');
	}
	if (n != -1 && p_nl)
		n = add_block(&listed_lns[fd], buffer, p_nl - buffer + 1, &ln);
	if (n != -1 && listed_lns[fd])
		construct_line(&listed_lns[fd], &ln);
	if (n != -1 && p_nl && *++p_nl)
		n = add_block(&listed_lns[fd], p_nl, ft_strchr(p_nl, '\0') - p_nl, &ln);
	return (ln);
}
