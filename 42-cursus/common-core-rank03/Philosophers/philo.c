/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/01 03:44:13 by rtorrent         ###   ########.fr       */
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
	struct timeval	t;
	const int		error_status = gettimeofday(&t, NULL);
	char			timestamp[12];

	if (!error_status
		&& !tstamp(timestamp, dst, (const struct timeval *[2]){t0, &t},
		&philo->pdata->shared_locks[DATA_RECORDING]))
		printf("%s %i %s\n", timestamp, philo->n, str);
	return (error_status);
}

void	destroy_forks(t_data *pdata, t_fork *fork, int error)
{
	t_fork *const	last = pdata->fork + pdata->number_of_philos;
	int				i;

	i = 0;
	while (i < NUMBER_OF_LOCKS)
		error = (pthread_mutex_destroy(pdata->shared_locks + i++) || error);
	while (fork < last)
		error = (pthread_mutex_destroy(&fork++->lock) || error);
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
			data.exit_status = (data.exit_status || philo->result);
		}
		destroy_forks(&data, data.fork, 0);
	}
	free(data.shared_locks);
	free(data.fork);
	free(data.philo);
	return (data.exit_status);
}
