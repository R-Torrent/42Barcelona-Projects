/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/02 03:25:32 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	place_digit(long n, char **pstr)
{
	long	x;

	x = n / 10L;
	if (x)
		place_digit(x, pstr);
	if (n < 0)
		x = '0' - n % 10L;
	else
		x = '0' + n % 10L;
	*(*pstr)++ = x;
}

static int	tstamp(char *timestamp, unsigned int *dst,
		const struct timeval *t[2], pthread_mutex_t *lock)
{
	long	elapsed;
	int		err;

	err = 0;
	elapsed = (long)(t[1]->tv_sec - t[0]->tv_sec) * 1000L
		+ (long)(t[1]->tv_usec - t[0]->tv_usec) / 1000L;
	if (dst)
	{
		err = pthread_mutex_lock(lock);
		if (!err)
		{
			*dst = (unsigned int)elapsed;
			err = pthread_mutex_unlock(lock);
		}
	}
	if (!err)
	{
		if (elapsed < 0)
			*timestamp++ = '-';
		place_digit(elapsed, &timestamp);
		*timestamp = '\0';
	}
	return (err);
}

int	print_stamp(unsigned int *dst, const struct timeval *t0, t_philo *philo,
		const char *str)
{
	pthread_mutex_t *const	print_lock = philo->pdata->shared_locks + PRINT_LOG;
	pthread_mutex_t *const	access_lock = &philo->access;
	struct timeval			t;
	int						err;
	char					timestamp[12];

	err = (gettimeofday(&t, NULL)
			|| tstamp(timestamp, dst, (const struct timeval *[2]){t0, &t},
				access_lock)
			|| pthread_mutex_lock(print_lock));
	if (!err)
	{
		printf("%s %i %s\n", timestamp, philo->n, str);
		err = pthread_mutex_unlock(print_lock);
	}
	return (err);
}

void	destroy_locks(t_data *pdata, t_fork *fork, int error)
{
	t_fork *const	lastf = pdata->fork + pdata->number_of_philos;
	t_philo *const	lastp = pdata->philo + pdata->number_of_philos;
	t_philo			*philo;
	int				i;

	i = 0;
	while (i < NUMBER_OF_LOCKS)
		error = (pthread_mutex_destroy(pdata->shared_locks + i++) || error);
	while (fork < lastf)
		error = (pthread_mutex_destroy(&fork++->lock) || error);
	philo = pdata->philo;
	while (philo < lastp)
		error = (pthread_mutex_destroy(&philo++->access) || error);
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct timeval	t0;
	struct s_philo	*philo;

	data.t0 = &t0;
	if (load_sim(&data, --argc, ++argv))
	{
		philo = data.philo + data.number_of_philos;
		while (philo-- > data.philo)
		{
			pthread_join(philo->thread, NULL);
			data.exit_status = (data.exit_status || (philo->flags & PHILO_ERR));
		}
		destroy_locks(&data, data.fork, 0);
	}
	free(data.shared_locks);
	free(data.fork);
	free(data.philo);
	return (data.exit_status);
}
