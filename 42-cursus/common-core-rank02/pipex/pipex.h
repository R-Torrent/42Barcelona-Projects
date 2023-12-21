/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:31:39 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/21 13:01:29 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

/* ************************************************************************** */

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

// external declarations from the libc (AKA 'authorized functions')
int		access(const char *pathname, int mode);
int		close(int fildes);
int		dup(int fildes);
int		dup2(int fildes, int fildes2);
int		execve(const char *path, char *const argv[], char *const envp[]);
void	exit(int status);
pid_t	fork(void);
void	free(void *ptr);
void	*malloc(size_t size);
int		open(const char *pathname, int flags, ...);
void	perror(const char *s);
int		pipe(int fildes[2]);
ssize_t	read(int fildes, void *buf, size_t nbyte);
char	*strerror(int errnum);
int		unlink(const char *path);
pid_t	wait(int *stat_loc);
pid_t	waitpid(pid_t pid, int *stat_loc, int options);
ssize_t	write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

# define RDR_INPUT   0
# define RDR_OUTPUT  1
# define RDR_APPOUT  2
# define RDR_HEREDOC 3

# define COMMAND_NOT_FOUND 127
# define COMMAND_NOT_EXECUTABLE 126

typedef struct s_data
{
	char	*pipex_name;
	t_list	*pipeline;
	char	**paths;
}	t_data;

typedef struct s_commands
{
	char	**words;
	t_list	*redir;
}	t_comm;

typedef struct s_redirection
{
	char	*word;
	int		type;
}	t_redir;

void	child_exit(t_data *const pdata, int exit_status);
void	link_pipeline(t_data *const pdata, char *const *envp);
void	parse_pipeline(t_data *const pdata, const int argc, char *const argv[]);
void	terminate(t_data *const pdata, const int exit_stats, int xtra_fds, ...);

// future 'libft' addition (stdlib.h) needed for the project
char	*ft_getenv(const char *name);

/* ************************************************************************** */

#endif
