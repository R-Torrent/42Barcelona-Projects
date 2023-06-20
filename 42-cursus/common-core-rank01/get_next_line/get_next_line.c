/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:22:56 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/20 17:12:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*listed_lines[MAX_FILES];
	char			buffer[BUFFER_SIZE + 1];
	int				nc;
	char			*pos_newline;

	nc = read(fd, buff, BUFFER_SIZE);
	if (nc == -1)
		return (NULL);
	while (nc)
	{
		buffer[nc] = '\0';
		pos_newline = ft_strchr(buffer, '\n');
		if (!pos_newline)
		{
			ft_lstadd_back(&listed_lines[fd], ft_lstnew(ft_strdup(buffer)));
		}
		nc = read(fd, buff, BUFFER_SIZE);
	}
}
