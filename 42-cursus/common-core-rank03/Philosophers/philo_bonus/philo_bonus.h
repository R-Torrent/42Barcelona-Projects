/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:10:13 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/15 14:11:13 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* ************************************************************************** */

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

// external declarations from the libc (AKA 'authorized functions')
void	exit(int status);
pid_t	fork(void);
void	free(void *ptr);
int		gettimeofday(struct timeval *tv, struct timezone *tz);
int		kill(pid_t pid, int sig);
void	*malloc(size_t size);
int		printf(const char *format, ...);
int		pthread_create(pthread_t *thread, const pthread_attr_t *attr,
			void *(*start_routine) (void *), void *arg);
int		pthread_detach(pthread_t thread);
int		pthread_join(pthread_t thread, void **retval);
int		sem_close(sem_t *sem);
sem_t	*sem_open(const char *name, int oflag, ...);
int		sem_post(sem_t *sem);
int		sem_unlink(const char *name);
int		sem_wait(sem_t *sem);
int		usleep(useconds_t usec);
pid_t	waitpid(pid_t pid, int *wstatus, int options);
ssize_t	write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

// delay to stop waking philos from jumping the queue, in microseconds
# define SLEEP_N_THINK 200U

enum e_philo_action
{
	THINK,
	PICK,
	EAT,
	SLEEP,
	NUMBER_OF_ACTIONS
};

// O_CREAT = 0100
# define S_OFLAG 0100
// S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH = 0644
# define S_MODE 0644

/* semaphore uses:
 * MASTR: synchronize all philosophers and their controllers
 * PRINT: print each log
 * FORKS: as per instructions, a semaphore for the pile of forks
 * MLSOK: optional argument 'number_of_times_each_philosopher_must_eat'
 * TERMN: simulation terminates, from death, MLSOK, or program error
 * NUMBS (keep last): as last element in enumeration, will store the amount
*/

enum e_semaphores
{
	MASTR,
	PRINT,
	FORKS,
	MLSOK,
	TERMN,
	NUMBS
};

typedef struct s_philo
{
	int				n;
	int				meals_left;
	unsigned int	last_meal;
	sem_t			*access;
	sem_t			*read_time;
	struct s_contrl	*contrl;
}	t_philo;

typedef struct s_contrl
{
	char			timestamp[12];
	unsigned int	elapsed;
	int				ret;
	pthread_t		thread_controller;
	pthread_t		thread_cleaner;
	struct timeval	*t;
	struct s_data	*pdata;
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
	pthread_t		terminator;
	sem_t			**shared_sems;
	struct s_philo	*philo;
	pid_t			*pid;
}	t_data;

// philosopher actions
typedef int	(*t_philo_func)(struct s_philo *);

int		load_sim(t_data *pdata, int params, char **args);
void	loop_philo(t_philo *philo);
int		print_stamp(unsigned int *dst, t_philo *philo, const char *str);
void	run_cleaner(t_data *pdata);
void	run_philo(t_philo *philo);
char	*sem_name(char *sname, int n, const char *suffix);
int		tstamp(t_contrl *contrl);
int		wait_usec(t_contrl *contrl, unsigned int lapse, int is_contrl);

/* ************************************************************************** */

#endif
