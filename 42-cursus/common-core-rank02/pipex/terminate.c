/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:52:36 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/04 11:50:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	del_comm(void *commv)
{
	t_comm *const	comm = (t_comm *)commv;
	char **const	words0 = comm->words;

	free(comm->binary);
	while (*comm->words)
		free(*comm->words++);
	free(words0);
	ft_lstclear(&comm->redir, free);
	free(comm);
}

void	del_data(t_data *const pdata)
{
	char **const	paths0 = pdata->paths;

	ft_lstclear(&pdata->pipeline, del_comm);
	while (*pdata->paths)
		free(*pdata->paths++);
	free(paths0);
}

void	terminate(t_data *const pdata, const int exit_stats, int xtra_fds, ...)
{
	va_list	ap;
	int		fd;

	if (xtra_fds)
	{
		va_start(ap, xtra_fds);
		while (xtra_fds--)
		{
			fd = va_arg(ap, int);
			if (fd != -1)
				close(fd);
		}
		va_end(ap);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (exit_stats == EXIT_FAILURE)
		perror(pdata->pipex_name);
	del_data(pdata);
	exit(exit_stats);
}
