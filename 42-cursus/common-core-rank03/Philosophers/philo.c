/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/30 18:22:29 by rtorrent         ###   ########.fr       */
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

char	*tstamp(char *timestamp, struct timeval *t0, struct timeval *t)
{
	char *const	timestamp0 = timestamp;
	long		elapsed;

	elpased = (long)(t->tv_sec - t0->tv_sec) * 1000L
		+ (long)(t->tv_usec - t0->tv_usec) / 1000L;
	if (elapsed < 0)
		*timestamp++ = '-';
	place_digit(elapsed, &timestamp);
	*timestamp = '\0';
	return (timestamp0);
}

void	destroy_forks(t_data *pdata, t_fork *fork, int error)
{
	t_fork *const	last = pdata->fork + pdata->number_of_philos;

	error = (pthread_mutex_destroy(pdata->forks_locked) || error);
	while (fork < last)
		error = (pthread_mutex_destroy(&fork++->lock) || error);
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct timeval	t0;
	pthread_mutex_t	forks_locked;
	pthread_t		*philo;
	int				*philo_result;

	data.forks_locked = &forks_locked;
	data.t0 = &t0;
	if (load(&data, --argc, ++argv))
	{
		philo = data.philo + data.number_of_philos;
		while (philo-- > data.philo)
			pthread_join(*philo, NULL);
		philo_result = data.philo_result + data.number_of_philos;
		while (philo_result-- > data.philo_result)
			data.exit_status = (data.exit_status || *philo_result);
		destroy_forks(&data, data.fork, 0);
	}
	free(data.fork);
	free(data.philo);
	free(data.philo_args);
	return (data.exit_status);
}
