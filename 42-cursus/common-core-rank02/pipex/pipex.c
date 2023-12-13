/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:41:44 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/12 21:02:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

// this function replaces 'getenv("SHELL")', of the 'stdlib' header
char	*get_shell(char **env)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "SHELL=", 6))
			return (*env + 6);
		env++;
	}
	return ("/bin/sh");
}

int	main(int argc, char *argv[], char *envp[])
{
	char *const	binary_path = get_shell(envp);
	char		*args[4] = {binary_path, "-c"};
	int			fd[2];
	pid_t		child_pid;

	if (argc == 3)
	{
		if (!pipe(fd))
		{
			child_pid = fork();
			if (child_pid == 0)
			{
				close(fd[0]);
				if (dup2(fd[1], 1) > -1)
				{
					close(fd[1]);
					args[2] = argv[1];
					execve(binary_path, args, envp);
				}
			}
			if (child_pid > 0)
			{
				close(fd[1]);
				if (dup2(fd[0], 0) > -1)
				{
					close(fd[0]);
					args[2] = argv[2];
					execve(binary_path, args, envp);
				}
			}
		}
		perror(argv[0]);
	}
	exit(EXIT_FAILURE);
}
