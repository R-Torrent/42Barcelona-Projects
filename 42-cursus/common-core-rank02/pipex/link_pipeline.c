/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:26:24 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/06 18:43:48 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_exit(char *const command, const int exit_stats, int xtra_fds, ...)
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
	perror(command);
	exit(exit_stats);
}

void	redir_command(const t_list *redir, char *const pipex_name)
{
	t_redir *const	rdr = redir->content;
	int				flags;
	const int		mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	int				target;
	int				fd;

	flags = O_RDONLY;
	target = STDIN_FILENO;
	if (rdr->type == RDR_OUTPUT || rdr->type == RDR_APPOUT)
	{
		flags = O_CREAT | O_WRONLY;
		if (rdr->type == RDR_APPOUT)
			flags |= O_APPEND;
		target = STDOUT_FILENO;
	}
	fd = open(rdr->word, flags, mode);
	if ((fd == -1) | (dup2(fd, target) == -1) | close(fd))
		child_exit(pipex_name, EXIT_FAILURE, 0);
	if (redir->next)
		redir_command(redir->next, pipex_name);
}

void	exec_pln(t_comm *const comm, char *const *envp, char *pipex_name)
{
	if (comm->redir)
		redir_command(comm->redir, pipex_name);
	if (!comm->binary)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", pipex_name);
		pipex_name = comm->words[0];
		errno = ENOENT;
		child_exit(pipex_name, COMMAND_NOT_FOUND, 0);
	}
	if (access(comm->binary, X_OK))
	{
		ft_dprintf(STDERR_FILENO, "%s: ", pipex_name);
		pipex_name = comm->words[0];
		child_exit(pipex_name, COMMAND_NOT_EXECUTABLE, 0);
	}
	execve(comm->binary, comm->words, envp);
	child_exit(pipex_name, EXIT_FAILURE, 0);
}

void	link_pln(t_list *const pln, char *const *envp, char *const pipex_name)
{
	int		fd[2];
	pid_t	child_pid;

	if (pln->next)
	{
		if (pipe(fd) == -1)
			child_exit(pipex_name, EXIT_FAILURE, 0);
		child_pid = fork();
		if (child_pid == -1)
			child_exit(pipex_name, EXIT_FAILURE, 2, fd[0], fd[1]);
		if (!child_pid)
		{
			if (close(fd[0]) | (dup2(fd[1], STDOUT_FILENO) == -1)
				| close(fd[1]))
				child_exit(pipex_name, EXIT_FAILURE, 0);
			link_pln(pln->next, envp, pipex_name);
		}
		if (close(fd[1]) | (dup2(fd[0], STDIN_FILENO) == -1) | close(fd[0]))
			child_exit(pipex_name, EXIT_FAILURE, 0);
	}
	exec_pln(pln->content, envp, pipex_name);
}
