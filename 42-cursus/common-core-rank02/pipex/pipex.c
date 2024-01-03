/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:41:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/03 02:01:36 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;
	pid_t	child_pid;
	int		wstatus;

	data.pipex_name = ft_strrchr(argv[0], '/') + 1;
	data.pipeline = NULL;
	data.paths = ft_split(ft_getenv("PATH"), ':');
	parse_pipeline(&data.pipeline, argc, argv);
	child_pid = fork();
	if (!child_pid)
		link_pipeline(&data, envp);
	if (child_pid == -1 || wait(&wstatus) == -1)
		terminate(&data, EXIT_FAILURE, 0);
	if (WIFEXITED(wstatus))
		terminate(&data, WEXITSTATUS(wstatus), 0);
	terminate(&data, EXIT_SUCCESS, 0);
}
