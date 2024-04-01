/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:39:46 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/01 19:49:40 by rtorrent         ###   ########.fr       */
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
void	free(void *ptr);
int		gettimeofday(struct timeval *tv, struct timezone *tz);
void	*malloc(size_t size);
void	*memset(void *s, int c, size_t n);
int		printf(const char *format, ...);
int		pthread_create(pthread_t *thread, const pthread_attr_t *attr,
			void *(*start_routine) (void *), void *arg);
int		pthread_detach(pthread_t thread);
int		pthread_join(pthread_t thread, void **retval);
int		pthread_mutex_destroy(pthread_mutex_t *mutex);
int		pthread_mutex_init(pthread_mutex_t *restrict mutex,
			const pthread_mutexattr_t *restrict attr);
int		pthread_mutex_lock(pthread_mutex_t *mutex);
int		pthread_mutex_unlock(pthread_mutex_t *mutex);
int		usleep(useconds_t usec);
ssize_t	write(int fildes, const void *buf, size_t nbyte);

/* ************************************************************************** */

// minimum waiting period between fork retrials, in microseconds
# define DELAY_FORK_RE 10U

enum e_hand
{
	LEFT,
	RIGHT
};

enum e_philo_status
{
	THINKING,
	PICKING,
	EATING,
	DROPPING,
	SLEEPING
};

enum e_shared_locks
{
	FORK_PICKING,
	DATA_RECORDING,
	PRINT_LOG,
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
	int				result;
	struct s_fork	*fork[2];
	struct s_data	*pdata;
	pthread_t		thread;
}	t_philo;

// NOTE: time_to_X variables stored in microseconds
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
}	t_data;

void	destroy_forks(t_data *pdata, t_fork *fork, int error);
int		load_sim(t_data *pdata, int params, char **args);
int		print_stamp(unsigned int *dst, const struct timeval *t0, t_philo *philo,
			const char *str);
void	*run_philo(t_philo *philo);

/* ************************************************************************** */

#endif
