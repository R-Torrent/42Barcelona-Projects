/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:10:13 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/29 11:11:12 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

// external declarations from the libc (AKA 'authorized functions')
void			exit(int status);
pid_t			fork(void);
void			free(void *ptr);
int				gettimeofday(struct timeval *tv, struct timezone *tz);
int				kill(pid_t pid, int sig);
void			*malloc(size_t size);
void			*memset(void *s, int c, size_t n);
int				printf(const char *format, ...);
int				pthread_create(pthread_t *thread, const pthread_attr_t *attr,
					void *(*start_routine) (void *), void *arg);
int				pthread_detach(pthread_t thread);
int				pthread_join(pthread_t thread, void **retval);
int				sem_close(sem_t *sem);
sem_t			*sem_open(const char *name, int oflag, mode_t mode,
					unsigned int value);
int				sem_post(sem_t *sem);
int				sem_unlink(const char *name);
int				sem_wait(sem_t *sem);
int				usleep(useconds_t usec);
pid_t			waitpid(pid_t pid, int *wstatus, int options);
ssize_t			write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

// delay to stop waking philos from jumping the queue, in microseconds
# define SLEEP_N_THINK 800U

enum e_hand
{
	LEFT,
	RIGHT
};

enum e_philo_action
{
	THINK,
	PICK,
	EAT,
	SLEEP,
	NUMBER_OF_ACTIONS
};

// philosopher flags
# define PHILO_ERR 01
# define MEALS__OK 02
# define TERMINATE 04

enum e_shared_locks
{
	MASTER_LOCK,
	READ_TIME,
	PRINT_LOG,
	NUMBER_OF_LOCKS
};

typedef struct s_fork
{
	int				n;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_philo
{
	int				n;
	int				meals_left;
	unsigned int	last_meal;
	int				flags;
	struct s_fork	*fork[2];
	struct s_data	*pdata;
	pthread_mutex_t	access;
	pthread_t		thread;
}	t_philo;

typedef struct s_contrl
{
	char			timestamp[12];
	unsigned int	elapsed;
	int				flags;
	struct timeval	*t;
	struct s_data	*pdata;
	pthread_t		thread;
}	t_contrl;

// NOTE: all times stored in microseconds
typedef struct s_data
{
	int				number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	int				exit_status;
	pthread_mutex_t	*shared_locks;
	struct s_fork	*fork;
	struct s_philo	*philo;
	struct s_contrl	*contrl;
}	t_data;

// philosopher actions
typedef int	(*t_philo_func)(struct s_philo *);

void			destroy_locks(t_data *pdata, t_fork *fork, int error);
int				load_sim(t_data *pdata, int params, char **args);
int				print_stamp(unsigned int *dst, t_philo *philo, const char *str);
void			*run_contrl(t_data *pdata);
void			*run_philo(t_philo *philo);
int				tstamp(t_contrl *contrl);
int				wait_usec(t_contrl *contrl, unsigned int lapse, int is_contrl);

/* ************************************************************************** */

#endif
