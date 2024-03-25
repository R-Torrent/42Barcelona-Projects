/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:39:46 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/25 18:55:30 by rtorrent         ###   ########.fr       */
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

struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				exit_status;
	pthread_t		*philo;
	pthread_mutex_t	*fork;
};

void	destroy_forks(struct s_data *pdata, pthread_mutex_t *last, int error);
int		load_sim(struct s_data *pdata, int param, char **args);

/* ************************************************************************** */

#endif
