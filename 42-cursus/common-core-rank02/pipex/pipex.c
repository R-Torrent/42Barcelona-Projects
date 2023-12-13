/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:41:44 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/13 04:06:05 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// code for args[0] replaces 'getenv("SHELL")', of the 'stdlib' header
void	set_args(char *args[static 4], char **env)
{
	args[0] = NULL;
	while (*env && !*args)
	{
		if (!ft_strncmp(*env, "SHELL=", 6))
			*args = *env + 6;
		env++;
	}
	if (!*args)
		*args = DEFAULT_SHELL;
	args[1] = "-c";
	args[3] = NULL;
}

void	redirect_fds(int pipe_fd1, int pipe_fd2, int new_fd)
{
	close(pipe_fd1);
	dup2(pipe_fd2, new_fd);
	close(pipe_fd2);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*args[4];
	int		fd[2];
	pid_t	child_pid;

	set_args(args, envp);
	while (--argc)
	{
		args[2] = argv[argc];
		if (argc > 1)
		{
			if (pipe(fd) == -1)
				break ;
			child_pid = fork();
			if (child_pid > 0)
				redirect_fds(fd[1], fd[0], 0);
			else if (!child_pid)
			{
				redirect_fds(fd[0], fd[1], 1);
				continue ;
			}
			else
				break ;
		}
		execve(args[0], args, envp);
	}
	perror(argv[0]);
	exit(EXIT_FAILURE);
}
