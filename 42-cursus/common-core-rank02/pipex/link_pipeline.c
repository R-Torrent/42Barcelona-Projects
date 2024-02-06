/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:26:24 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/06 21:21:18 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_exit(char *const command, const int exit_stats, int xtra_fds, ...)
{
	va_list	ap;
	int		fd;

	if (command)
		perror(command);
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
	exit(exit_stats);
}

void	redir_heredoc(char **const dlimitr, t_data *const pdata)
{
	const int	fdhd = open(TMP_HEREDOC, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	char		*line;
	size_t		len_dlmtr;

	len_dlmtr = ft_strlen(*dlimitr);
	while (fdhd != -1)
	{
		ft_putstr_fd(PROMPT_HEREDOC, pdata->std_fds[1]);
		line = ft_getnextline_fd(pdata->std_fds[0]);
		if (!line || (!ft_strncmp(line, *dlimitr, len_dlmtr)
				&& line[len_dlmtr] == '\n'))
		{
			free(line);
			if (close(fdhd))
				break ;
			*dlimitr = TMP_HEREDOC;
			return ;
		}
		ft_putstr_fd(line, fdhd);
		free(line);
	}
	ft_dprintf(STDERR_FILENO, "%s: ", pdata->pipex_name);
	child_exit(TMP_HEREDOC, CHILD_FAILURE,
		3, fdhd, pdata->std_fds[0], pdata->std_fds[1]);
}

void	target_n_flags(int type, int *target, int *flags)
{
	if (type == RDR_INPUT || type == RDR_HEREDOC)
	{
		*target = STDIN_FILENO;
		*flags = O_RDONLY;
	}
	else
	{
		*target = STDOUT_FILENO;
		*flags = O_CREAT | O_WRONLY;
		if (type == RDR_APPOUT)
			*flags |= O_APPEND;
	}
}

void	redir_command(const t_list *redir, t_data *const pdata)
{
	t_redir *const	rdr = redir->content;
	int				target;
	int				flags;
	int				fd;

	target_n_flags(rdr->type, &target, &flags);
	if (rdr->type == RDR_HEREDOC)
		redir_heredoc(&rdr->word, pdata);
	fd = open(rdr->word, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", pdata->pipex_name,
			rdr->word, strerror(ENOENT));
		child_exit(NULL, CHILD_FAILURE,
			2, pdata->std_fds[0], pdata->std_fds[1]);
	}
	if (dup2(fd, target) == -1)
		child_exit(pdata->pipex_name, CHILD_FAILURE,
			3, fd, pdata->std_fds[0], pdata->std_fds[1]);
	if (close(fd))
		child_exit(pdata->pipex_name, CHILD_FAILURE,
			2, pdata->std_fds[0], pdata->std_fds[1]);
	if (redir->next)
		redir_command(redir->next, pdata);
}

void	exec_pln(t_comm *const comm, char *const *envp, t_data *const pdata)
{
	if (comm->redir)
		redir_command(comm->redir, pdata);
	if (close(pdata->std_fds[0]) | close(pdata->std_fds[1]))
		child_exit(comm->words[0], CHILD_FAILURE, 0);
	if (!comm->binary)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", pdata->pipex_name,
			comm->words[0], "command not found");
		child_exit(NULL, COMMAND_NOT_FOUND, 0);
	}
	if (access(comm->binary, X_OK))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", pdata->pipex_name,
			comm->binary, strerror(EACCES));
		child_exit(NULL, COMMAND_NOT_EXECUTABLE, 0);
	}
	execve(comm->binary, comm->words, envp);
	ft_dprintf(STDERR_FILENO, "%s: ", pdata->pipex_name);
	child_exit(comm->words[0], CHILD_FAILURE, 0);
}

void	link_pln(t_list *const pln, char *const *envp, t_data *const pdata)
{
	int		fd[2];
	pid_t	child_pid;

	if (pln->next)
	{
		if (pipe(fd) == -1)
			child_exit(pdata->pipex_name, CHILD_FAILURE,
				2, pdata->std_fds[0], pdata->std_fds[1]);
		child_pid = fork();
		if (child_pid == -1 || (child_pid && dup2(fd[0], STDIN_FILENO) == -1)
			|| (!child_pid && dup2(fd[1], STDOUT_FILENO) == -1))
			child_exit(pdata->pipex_name, CHILD_FAILURE,
				4, fd[0], fd[1], pdata->std_fds[0], pdata->std_fds[1]);
		if (close(fd[0]) | close(fd[1]))
			child_exit(pdata->pipex_name, CHILD_FAILURE,
				2, pdata->std_fds[0], pdata->std_fds[1]);
		if (!child_pid)
			link_pln(pln->next, envp, pdata);
	}
	exec_pln(pln->content, envp, pdata);
}
