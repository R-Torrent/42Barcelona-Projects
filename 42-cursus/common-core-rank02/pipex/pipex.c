/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:41:44 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/13 14:13:13 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// code for args[0] replaces 'getenv("SHELL")', of the 'stdlib' header
void	set_args_open_files(char *args[], char **env, int argc_m1, char *argv[])
{
	const int	fd0 = open(argv[1], O_RDONLY);
	const int	fd1 = open(argv[argc_m1], O_CREAT | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

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
	if (fd0 == -1 || fd1 == -1 || dup2(fd0, 0) == -1 || dup2(fd1, 1) == -1)
		terminate_error(fd0, fd1, argv[0]);
	if (close(fd0) != -1 && close(fd1) != -1)
		return ;
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

void	terminate_error(int fd0, int fd1, char *filename)
{
	perror(filename);
	if (fd0 != -1)
		close(fd0);
	if (fd1 != -1)
		close(fd1);
	exit(EXIT_FAILURE);
}

void	redirect_fds(int pipe_fd1, int pipe_fd2, int new_fd, char *filename)
{
	const int	status0 = dup2(pipe_fd2, new_fd);
	const int	status1 = close(pipe_fd1);
	const int	status2 = close(pipe_fd2);

	if (status0 == -1 || status1 == -1 || status2 == -1)
		terminate_error(0, 1, filename);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*args[4];
	int		fd[2];
	pid_t	child_pid;

	set_args_open_files(args, envp, --argc, argv);
	while (--argc)
	{
		args[2] = argv[argc];
		if (argc > 2)
		{
			if (pipe(fd) == -1)
				terminate_error(0, 1, argv[0]);
			child_pid = fork();
			if (child_pid == -1)
				terminate_error(fd[0], fd[1], argv[0]);
			else if (!child_pid)
			{
				redirect_fds(fd[0], fd[1], 1, argv[0]);
				continue ;
			}
			redirect_fds(fd[1], fd[0], 0, argv[0]);
		}
		execve(args[0], args, envp);
		terminate_error(0, 1, argv[0]);
	}
}
