/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:39:46 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/30 15:16:02 by rtorrent         ###   ########.fr       */
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
# define DELAY_FORK_RE 100U

enum e_hand
{
	LEFT,
	RIGHT
};

// NOTE: time_to_X variables stored in microseconds
typedef struct s_data
{
	int				number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				number_of_times_each_philo_must_eat;
	int				exit_status;
	struct timeval	*t0;
	pthread_mutex_t	*forks_locked;
	pthread_mutex_t	*fork;
	int				*fork_held;
	pthread_t		*philo;
	struct s_args	*philo_args;
	int				*philo_result;
}	t_data;

struct s_args
{
	struct s_data	*pdata;
	int				nphilo;
};

void	destroy_forks(t_data *pdata, pthread_mutex_t *fork, int error);
int		drop_forks(t_data *const pdata, const int nphilo, const int *nforks,
			char *timestamp);
int		eat(t_data *const pdata, const int nphilo, char *timestamp);
int		load(t_data *pdata, int params, char **args, struct timeval *t0);
int		pick_forks(t_data *const pdata, const int nphilo, const int *nforks,
			char *timestamp);
int		sleep(t_data *const pdata, const int nphilo, char *timestamp));
int		think(t_data *const pdata, const int nphilo, char *timestamp);
char	*tstamp(char *timestamp, struct timeval *t0, struct timeval *t);

/* ************************************************************************** */

#endif
