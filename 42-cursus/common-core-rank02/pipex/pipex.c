/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:41:44 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/16 03:43:49 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	terminate_error(char *filename, int fd0, int fd1)
{
	perror(filename);
	if (fd0 != -1)
		close(fd0);
	if (fd1 != -1)
		close(fd1);
	exit(EXIT_FAILURE);
}

void	open_files(const char *const infile, const char *const outfile, const int append)
{
	int	fd0 = open(argv[1], O_RDONLY);
	int	fd1 = open(argv[argc_m1], O_CREAT | O_WRONLY | append, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd0 == -1)
		exit(EXIT_SUCCESS);
	if (fd0 == -1 || fd1 == -1 || dup2(fd0, 0) == -1 || dup2(fd1, 1) == -1)
		terminate_error(fd0, fd1, argv[0]);
	if (close(fd0) != -1 && close(fd1) != -1)
		return ;
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

char	*find_comm(char *word, char *path)
{
	return (NULL);
}

void	*parse(t_list **ppipeln, int argc, char *argv[], char *path)
{
	const bool	here_doc = ft_strlen(argv[1]) == 8 && !ft_strncmp(argv[1], "here doc", 8);
	int			i;
	char		**words;
	t_redir		*const redir[2] = {malloc(sizeof(t_redir)), malloc(sizeof(t_redir))};

	i = 2 + here_doc;
	while (i < argc - 1)
	{
		words = ft_split(argv[i++], ' ');
		ft_lstadd_front(ppipeln, ft_lstnew(malloc(sizeof(t_comm))));
		*(*ppipeln)->content = (t_comm){words, find_comm(*words, path), NULL};
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
	ft_lstadd_back(&ft_lstlast(*ppipeln)->content->redir, ft_lstnew(redir[0]));
	ft_lstadd_back(&(*ppipeln)->content->redir, ft_lstnew(redir[1]));
}

int	main(int argc, char *argv[], char *envp[])
{
	char *const		command_name = ft_strrchr(argv[0], '/') + 1;
	t_list *		pipeline;
	int				fd[2];
	pid_t			child_pid;

	parse(&pipeline, argc, argv, ft_getenv("PATH"));
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
