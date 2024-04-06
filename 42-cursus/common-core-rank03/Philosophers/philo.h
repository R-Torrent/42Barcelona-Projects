/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:39:46 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/06 05:02:45 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */

# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

// external declarations from the libc (AKA 'authorized functions')
void			free(void *ptr);
int				gettimeofday(struct timeval *tv, struct timezone *tz);
void			*malloc(size_t size);
void			*memset(void *s, int c, size_t n);
int				printf(const char *format, ...);
int				pthread_create(pthread_t *thread, const pthread_attr_t *attr,
					void *(*start_routine) (void *), void *arg);
int				pthread_detach(pthread_t thread);
int				pthread_join(pthread_t thread, void **retval);
int				pthread_mutex_destroy(pthread_mutex_t *mutex);
int				pthread_mutex_init(pthread_mutex_t *restrict mutex,
					const pthread_mutexattr_t *restrict attr);
int				pthread_mutex_lock(pthread_mutex_t *mutex);
int				pthread_mutex_unlock(pthread_mutex_t *mutex);
int				usleep(useconds_t usec);
ssize_t			write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

// controller waiting period between evaluations, in microseconds
# define DELAY_CONTROLLER_REPEAT 500U

// minimum waiting period between fork retrials, in microseconds
# define FORK_RETRIAL 50U

// function return for a fork retrial
# define RETURN_FORK_RETRIAL -4

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
	FORK_PICKING,
	NUMBER_OF_LOCKS
};

typedef struct s_fork
{
	int				n;
	int				held;
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
	int			exit;
	pthread_t	thread;
}	t_contrl;

// NOTE: time_to_eat and time_to_sleep variables stored in microseconds;
// time_to_die kept in milliseconds
typedef struct s_data
{
	int				number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				exit_status;
	struct timeval	*t0;
	pthread_mutex_t	*shared_locks;
	struct s_fork	*fork;
	struct s_philo	*philo;
	struct s_contrl	*contrl;
}	t_data;

// philosopher actions
typedef int	(*t_philo_func)(struct s_philo *, struct timeval **);

void			destroy_locks(t_data *pdata, t_fork *fork, int error);
int				load_sim(t_data *pdata, int params, char **args);
int				print_stamp(unsigned int *dst, struct timeval **t,
					t_philo *philo, const char *str);
void			*run_controller(t_data *pdata);
void			*run_philo(t_philo *philo);
unsigned int	tstamp(char *timestamp, struct timeval **t);

/* ************************************************************************** */

#endif
