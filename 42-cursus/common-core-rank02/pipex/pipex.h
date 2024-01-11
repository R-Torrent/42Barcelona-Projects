/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:31:39 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/08 23:10:29 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

/* ************************************************************************** */

# include <errno.h>
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

// quoting flags
# define QUOT_SQ 01
# define QUOT_DQ 02

// redirection options
# define RDR_INPUT   0
# define RDR_OUTPUT  1
# define RDR_APPOUT  2
# define RDR_HEREDOC 3
# define TMP_HEREDOC "/tmp/hd"
# define PROMPT_HEREDOC "> "

# define COMMAND_NOT_FOUND 127
# define COMMAND_NOT_EXECUTABLE 126

typedef struct s_data
{
	char	*pipex_name;
	t_list	*pipeline;
	char	**paths;
	int		std_fds[2];
}	t_data;

typedef struct s_commands
{
	char	*binary;
	char	**words;
	t_list	*redir;
}	t_comm;

typedef struct s_redirection
{
	char	*word;
	int		type;
}	t_redir;

void	link_pln(t_list *const pln, char *const *envp, t_data *const pdata);
void	parse_pln(t_list **const ppln, char *const *paths, const int argc,
			char *const argv[]);

// additional 'libft' functions required for this project
// (stdio.h, stdlib.h, 'bonus list functions' and string.h, respectively)
int		ft_dprintf(int fd, const char *format, ...);
char	*ft_getenv(const char *name);
void	**ft_lsttoarray(t_list *lst);
size_t	ft_strspn(const char *s, const char *accept);

/* ************************************************************************** */

#endif
