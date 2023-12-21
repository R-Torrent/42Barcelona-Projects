/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:26:24 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/21 12:59:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_comm(t_data *const pdata, char *word)
{
	char		**paths;
	char *const	word1 = ft_strjoin("/", word);
	char		*full_path;

	if (!ft_strchr(word, '/'))
	{
		paths = pdata->paths;
		while (*paths)
		{
			full_path = ft_strjoin(*paths++, word1);
			if (!access(full_path, F_OK))
			{
				free(word1);
				if (!access(full_path, X_OK))
					return (full_path);
				child_exit(pdata, COMMAND_NOT_EXECUTABLE);
			}
			free(full_path);
		}
		free(word1);
		child_exit(pdata, COMMAND_NOT_FOUND);
	}
	if (access(word, F_OK))
		child_exit(pdata, COMMAND_NOT_FOUND);
	if (access(word, X_OK))
		child_exit(pdata, COMMAND_NOT_EXECUTABLE);
	return (word);
}

void	redir_command(t_data *const pdata, const t_list *redir)
{
	t_redir	*rdr;
	int		flags;
	int		mode;
	int		target;
	int		fd;

	while (redir)
	{
		rdr = redir->content;
		if (rdr->type == RDR_INPUT || rdr->type == RDR_HEREDOC)
		{
			flags = O_RDONLY;
			target = STDIN_FILENO;
		}
		else
		{
			flags = O_CREAT | O_WRONLY;
			if (rdr->type == RDR_APPOUT)
				flags |= O_APPEND;
			mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
			target = STDOUT_FILENO;
		}
		fd = open(rdr->word, flags, mode);
		if ((fd == -1) | (dup2(fd, target) == -1) | close(fd))
			child_exit(pdata, EXIT_FAILURE);
		redir = redir->next;
	}
}

void	exec_pipeline(t_data *const pdata, t_list *pln, char *const *envp)
{
	t_comm *const	comm = pln->content;

	redir_command(pdata, comm->redir);
	execve(find_comm(pdata, *comm->words), comm->words, envp);
	child_exit(pdata, EXIT_FAILURE);
}

void	link_pipeline(t_data *const pdata, char *const *envp)
{
	t_list	*pln;
	int		fd[2];
	pid_t	child_pid;

	pln = pdata->pipeline;
	while (pln)
	{
		if (pln->next)
		{
			if (pipe(fd) == -1)
				terminate(pdata, EXIT_FAILURE, 0);
			child_pid = fork();
			if (child_pid == -1)
				terminate(pdata, EXIT_FAILURE, 2, fd[0], fd[1]);
			if (!child_pid)
			{
				if (close(fd[0]) | (dup2(fd[1], STDOUT_FILENO) == -1) | close(fd[1]))
					terminate(pdata, EXIT_FAILURE, 0);
				pln = pln->next;
				continue ;
			}
			if (close(fd[1]) | (dup2(fd[0], STDIN_FILENO) == -1) | close(fd[0]))
				terminate(pdata, EXIT_FAILURE, 0);
		}
		exec_pipeline(pdata, pln, envp);
	}
}
