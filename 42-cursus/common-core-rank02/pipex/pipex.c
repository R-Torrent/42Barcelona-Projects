/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:41:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/04 22:20:38 by rtorrent         ###   ########.fr       */
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

void	terminate(t_data *const pdata, const int exit_status)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (exit_status == EXIT_FAILURE)
		perror(pdata->pipex_name);
	del_data(pdata);
	exit(exit_status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	pid_t	child_pid;
	int		wstatus;

	data.pipex_name = ft_strrchr(argv[0], '/') + 1;
	data.pipeline = NULL;
	data.paths = ft_split(ft_getenv("PATH"), ':');
	parse_pln(&data.pipeline, argc, argv);
	child_pid = fork();
	if (!child_pid)
		link_pln(&data, data.pipeline, envp);
	if (child_pid == -1 || wait(&wstatus) == -1 || !WIFEXITED(wstatus))
		terminate(&data, EXIT_FAILURE);
	terminate(&data, WEXITSTATUS(wstatus));
}
