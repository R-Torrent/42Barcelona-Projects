/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:31:39 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/11 04:33:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

/* ************************************************************************** */

# include <stdlib.h>
# include <sys/types.h>

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



/* ************************************************************************** */

#endif
