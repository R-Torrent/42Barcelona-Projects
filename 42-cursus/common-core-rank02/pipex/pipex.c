/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:41:44 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/14 22:09:22 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	terminate_error(int fd0, int fd1)
{
	perror(filename);
	if (fd0 != -1)
		close(fd0);
	if (fd1 != -1)
		close(fd1);
	exit(EXIT_FAILURE);
}

// code for args[0] replaces 'getenv("SHELL")', of the 'stdlib' header
void	set_args_open_files(char *args[], char **env, int argc_m1, char *argv[])
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

void	open_files(const char *const infile, const char *const outfile, const int append)
	int	fd0;
	int	fd1 = open(argv[argc_m1], O_CREAT | O_WRONLY | append,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	fd0 = open(argv[1], O_RDONLY);
	if (fd0 == -1)
		exit(EXIT_SUCCESS);
	if (fd0 == -1 || fd1 == -1 || dup2(fd0, 0) == -1 || dup2(fd1, 1) == -1)
		terminate_error(fd0, fd1, argv[0]);
	if (close(fd0) != -1 && close(fd1) != -1)
		return ;
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *const	command_name = ft_strrchr(argv[0], '/') + 1;
	int			fd[2];
	pid_t		child_pid;

	if (argc < 4)
		terminate_error(command_name, 2, 0, 1);
	open_files(argv[1], argv[--argc]);
	while (--argc)
	{
		if (argc > 2)
		{
			if (pipe(fd) == -1)
				terminate_error(2, 0, 1);
			child_pid = fork();
			if (child_pid == -1)
				terminate_error(command_name, 4, fd[0], fd[1], 0, 1);
			else if (!child_pid)
				if (close(fd[0]) | dup2(fd[1], 1) == -1 | close(fd[1]))
					terminate_error(command_name, 2, 0, 1);
				else
					continue ;
			if (close(fd[1]) | dup2(fd[0], 0) == -1 | close(fd[0]))
				terminate_error(command_name, 2, 0, 1);
		}
		execve(args[0], args, envp);
		terminate_error(command_name, 0, 1);
	}
}
