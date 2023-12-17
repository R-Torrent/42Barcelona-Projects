/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:41:44 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/17 19:51:30 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	del_redir(void *redir)
{
	free(((t_redir *)redir)->word);
	free(redir);
}

void	del_comm(void *commv)
{
	t_comm *const	comm = (t_comm *)commv;
	char **const	words0 = comm->words;

	while (comm->words)
		free(comm->words++);
	free(words0);
	free(comm->command);
	ft_lstclear(&comm->redir, del_redir);
	free(comm);
}

void	terminate(const char *filename, char **paths, t_list *pipeline, int n, ...)
{
	char **const	paths0 = paths;
	va_list			ap;
	int				fd;

	while (*paths)
		free(*paths++);
	free(paths0);
	ft_lstclear(&pipeline, del_comm);
	if (!filename)
		exit(n);
	perror(filename);
	va_start(ap, n);
	while (n--)
	{
		fd = va_arg(ap, int);
		if (fd != -1)
			close(fd);
	}
	va_end(ap);
	exit(EXIT_FAILURE);
}

/*
void	open_files(const char *const infile, const char *const outfile, const int append)
{
	int	fd0 = open(argv[1], O_RDONLY);
	int	fd1 = open(argv[argc_m1], O_CREAT | O_WRONLY | append, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd0 == -1)
		exit(EXIT_SUCCESS);
	if (fd0 == -1 || fd1 == -1 || dup2(fd0, 0) == -1 || dup2(fd1, 1) == -1)
		terminate(fd0, fd1, argv[0]);
	if (close(fd0) != -1 && close(fd1) != -1)
		return ;
	perror(argv[0]);
	exit(EXIT_FAILURE);
}
*/
void	redir_command(const t_list *redir)
{
	while (redir)
	{
		// CONTINUE HERE, REDIRECTING STDIN_FILENO & STDOUT_FILENO
		redir = redir -> next;
	}
}

void	exec_pipeline(t_list *pipeline, char *const *envp, const char *pipex_name, char **paths)
{
	int		fd[2];
	pid_t	child_pid;

	while (pipeline)
	{
		if (pipeline->next)
		{
			if (pipe(fd) == -1)
				terminate(pipex_name, paths, pipeline, 2, STDIN_FILENO, STDOUT_FILENO);
			child_pid = fork();
			if (child_pid == -1)
				terminate(pipex_name, paths, pipeline, 4, fd[0], fd[1], STDIN_FILENO, STDOUT_FILENO);
			if (!child_pid)
			{
				if (close(fd[0]) | (dup2(fd[1], STDOUT_FILENO) == -1) | close(fd[1]))
					terminate(pipex_name, paths, pipeline, 2, STDIN_FILENO, STDOUT_FILENO);
				pipeline = pipeline -> next;
				continue ;
			}
			if (close(fd[1]) | (dup2(fd[0], STDIN_FILENO) == -1) | close(fd[0]))
				terminate(pipex_name, paths, pipeline, 2, STDIN_FILENO, STDOUT_FILENO);
		}
		redir_command(((t_comm *)pipeline->content)->redir);
		execve(((t_comm *)pipeline->content)->command, ((t_comm *)pipeline->content)->words, envp);
		terminate(pipex_name, paths, pipeline, STDIN_FILENO, STDOUT_FILENO);
	}
}

char	*find_comm(char *word, char **paths)
{
	char	*word1;
	char	*full_path;

	if (ft_strchr(word, '/'))
		return (word);
	word1 = ft_strjoin("/", word);
	while (*paths)
	{
		full_path = ft_strjoin(*paths, word1);
		if (!access(full_path, X_OK))
		{
			free(word1);
			return (full_path);
		}
		errno = 0;
		free(full_path);
	}
	free(word1);
	return (word);
}

void	parse_pipeline(t_list **ppipeln, int argc, char *const argv[], char **paths)
{
	const bool		here_doc = ft_strlen(argv[1]) == 8 && !ft_strncmp(argv[1], "here doc", 8);
	int				i;
	char			**words;
	t_redir *const	redir[2] = {malloc(sizeof(t_redir)), malloc(sizeof(t_redir))};

	i = 2 + here_doc;
	while (i < argc - 1)
	{
		words = ft_split(argv[i++], ' ');
		ft_lstadd_front(ppipeln, ft_lstnew(malloc(sizeof(t_comm))));
		*(t_comm *)(*ppipeln)->content = (t_comm){words, find_comm(*words, paths), NULL};
	}
	if (here_doc)
	{
		*redir[0] = (t_redir){argv[2], RDR_HEREDOC};
		*redir[1] = (t_redir){argv[i], RDR_APPOUT};
	}
	else
	{
		*redir[0] = (t_redir){argv[1], RDR_INPUT};
		*redir[1] = (t_redir){argv[i], RDR_OUTPUT};
	}
	ft_lstadd_back(&((t_comm *)ft_lstlast(*ppipeln)->content)->redir, ft_lstnew(redir[0]));
	ft_lstadd_back(&((t_comm *)(*ppipeln)->content)->redir, ft_lstnew(redir[1]));
}

int	main(int argc, char *argv[], char *envp[])
{
	char *const		pipex_name = ft_strrchr(argv[0], '/') + 1;
	t_list			*pipeline;
	char **const	paths = ft_split(ft_getenv("PATH"), ':');
	pid_t			child_pid;
	int				wstatus;

	pipeline = NULL;
	parse_pipeline(&pipeline, argc, argv, paths);
	child_pid = fork();
	if (!child_pid)
		exec_pipeline(pipeline, envp, pipex_name, paths);
	if (child_pid == -1 || wait(&wstatus) == -1)
		terminate(pipex_name, paths, pipeline, 2, STDIN_FILENO, STDOUT_FILENO);
	if (WIFEXITED(wstatus))
		terminate(NULL, paths, pipeline, WEXITSTATUS(wstatus));
	terminate(NULL, paths, pipeline, EXIT_SUCCESS);
}
