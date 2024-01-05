/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:26:24 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/05 02:18:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_exit(t_data *const pdata, const int exit_stats, int xtra_fds, ...)
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
	perror(pdata->pipex_name);
	exit(exit_stats);
}

void	seek_binary(t_data *const pdata, char **pbinary, char *word)
{
	char	**paths;

	if (ft_strchr(word, '/'))
	{
		paths = NULL;
		*pbinary = ft_strdup(word);
	}
	else
	{
		word = ft_strjoin("/", word);
		paths = pdata->paths;
		while (*paths)
		{
			free(*pbinary);
			*pbinary = ft_strjoin(*paths, word);
			if (!access(*pbinary, F_OK))
				break ;
			paths++;
		}
		free(word);
	}
	if ((!paths && access(*pbinary, F_OK)) || (paths && !*paths))
		child_exit(pdata, COMMAND_NOT_FOUND, 0);
	if (access(*pbinary, X_OK))
		child_exit(pdata, COMMAND_NOT_EXECUTABLE, 0);
}		

void	redir_command(t_data *const pdata, const t_list *redir)
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
		child_exit(pdata, EXIT_FAILURE, 0);
	if (redir->next)
		redir_command(pdata, redir->next);
}

void	exec_pln(t_data *const pdata, t_comm *const comm, char *const *envp)
{
	if (comm->redir)
		redir_command(pdata, comm->redir);
	seek_binary(pdata, &comm->binary, *comm->words);
	execve(comm->binary, comm->words, envp);
	child_exit(pdata, EXIT_FAILURE, 0);
}

void	link_pln(t_data *const pdata, t_list *const pln, char *const *envp)
{
	int		fd[2];
	pid_t	child_pid;

	if (pln->next)
	{
		if (pipe(fd) == -1)
			child_exit(pdata, EXIT_FAILURE, 0);
		child_pid = fork();
		if (child_pid == -1)
			child_exit(pdata, EXIT_FAILURE, 2, fd[0], fd[1]);
		if (!child_pid)
		{
			if (close(fd[0]) | (dup2(fd[1], STDOUT_FILENO) == -1)
				| close(fd[1]))
				child_exit(pdata, EXIT_FAILURE, 0);
			link_pln(pdata, pln->next, envp);
		}
		if (close(fd[1]) | (dup2(fd[0], STDIN_FILENO) == -1) | close(fd[0]))
			child_exit(pdata, EXIT_FAILURE, 0);
	}
	exec_pln(pdata, pln->content, envp);
}
