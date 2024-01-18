/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:26:24 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/18 01:26:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_exit(char *const command, const int exit_stats, int xtra_fds, ...)
{
	va_list	ap;
	int		fd;

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
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
	perror(command);
	exit(exit_stats);
}

void	redir_heredoc(const char *const dlimitr, int *fd_r, t_data *const pdata)
{
	const int	fd_w = open(TMP_HEREDOC, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	char		*line;

	*fd_r = open(TMP_HEREDOC, O_RDONLY);
	unlink(TMP_HEREDOC);
	while (fd_w != -1 && *fd_r != -1)
	{
		ft_putstr_fd(PROMPT_HEREDOC, pdata->std_fds[1]);
		line = ft_getnextline_fd(pdata->std_fds[0]);
		if (!line)
			break ;
		if (!ft_strncmp(line, dlimitr, ft_strlen(line) - 1))
		{
			free(line);
			if (close(fd_w) == -1)
				break ;
			return ;
		}
		ft_putstr_fd(line, fd_w);
		free(line);
	}
	ft_dprintf(STDERR_FILENO, "%s: ", pdata->pipex_name);
	child_exit(TMP_HEREDOC, EXIT_FAILURE, 2, fd_w, fd_r);
}

void	redir_command(const t_list *redir, t_data *const pdata)
{
	t_redir *const	rdr = redir->content;
	int				flags;
	int				target;
	int				fd;

	target = STDIN_FILENO;
	flags = O_RDONLY;
	if (rdr->type == RDR_OUTPUT || rdr->type == RDR_APPOUT)
	{
		flags = O_CREAT | O_WRONLY;
		if (rdr->type == RDR_APPOUT)
			flags |= O_APPEND;
		target = STDOUT_FILENO;
	}
	if (rdr->type == RDR_HEREDOC)
		redir_heredoc(rdr->word, &fd, pdata);
	else
		fd = open(rdr->word, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1 || ((dup2(fd, target) == -1) | close(fd)))
	{
		ft_dprintf(STDERR_FILENO, "%s: ", pdata->pipex_name);
		child_exit(rdr->word, EXIT_FAILURE, 0);
	}
	if (redir->next)
		redir_command(redir->next, pdata);
}

void	exec_pln(t_comm *const comm, char *const *envp, t_data *const pdata)
{
	if (comm->redir)
		redir_command(comm->redir, pdata);
	if (!comm->binary)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", pdata->pipex_name);
		errno = ENOENT;
		child_exit(comm->words[0], COMMAND_NOT_FOUND, 0);
	}
	if (access(comm->binary, X_OK))
	{
		ft_dprintf(STDERR_FILENO, "%s: ", pdata->pipex_name);
		child_exit(comm->words[0], COMMAND_NOT_EXECUTABLE, 0);
	}
	execve(comm->binary, comm->words, envp);
	ft_dprintf(STDERR_FILENO, "%s: ", pdata->pipex_name);
	child_exit(comm->words[0], EXIT_FAILURE, 0);
}

void	link_pln(t_list *const pln, char *const *envp, t_data *const pdata)
{
	int		fd[2];
	pid_t	child_pid;

	if (pln->next)
	{
		if (pipe(fd) == -1)
			child_exit(pdata->pipex_name, EXIT_FAILURE, 0);
		child_pid = fork();
		if (child_pid == -1)
			child_exit(pdata->pipex_name, EXIT_FAILURE, 2, fd[0], fd[1]);
		if (!child_pid)
		{
			if (close(fd[0]) | (dup2(fd[1], STDOUT_FILENO) == -1)
				| close(fd[1]))
				child_exit(pdata->pipex_name, EXIT_FAILURE, 0);
			link_pln(pln->next, envp, pdata);
		}
		if (close(fd[1]) | (dup2(fd[0], STDIN_FILENO) == -1) | close(fd[0]))
			child_exit(pdata->pipex_name, EXIT_FAILURE, 0);
	}
	exec_pln(pln->content, envp, pdata);
}
