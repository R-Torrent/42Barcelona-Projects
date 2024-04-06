/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/06 01:57:43 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	place_digit(unsigned int n, char **pstr)
{
	long	x;

	x = n / 10L;
	if (x)
		place_digit(x, pstr);
	x = '0' + n % 10L;
	*(*pstr)++ = x;
}

// elapsed simulation time, in milliseconds
unsigned int	tstamp(char *timestamp, struct timeval **t)
{
	const unsigned int	elapsed = (unsigned int)
		((t[1]->tv_sec - t[0]->tv_sec) * 1000
			+ (t[1]->tv_usec - t[0]->tv_usec) / 1000);

	if (timestamp)
	{
		place_digit(elapsed, &timestamp);
		*timestamp = '\0';
	}
	return (elapsed);
}

int	print_stamp(unsigned int *dst, struct timeval **t, t_philo *philo,
		const char *str)
{
	struct timeval	t1;
	unsigned int	elapsed;
	int				err;
	char			timestamp[12];

	if (!t[1])
	{
		if (gettimeofday(&t1, NULL))
			return (1);
		t[1] = &t1;
	}
	elapsed = tstamp(timestamp, t);
	err = pthread_mutex_lock(&philo->access);
	if (!err)
	{
		if (elapsed - philo->last_meal > philo->pdata->time_to_die)
			philo->flags |= TERMINATE;
		if (dst)
			*dst = elapsed;
		elapsed = philo->flags & TERMINATE;
		err = pthread_mutex_unlock(&philo->access);
	}
	if (!err && !elapsed)
		printf("%s %i %s\n", timestamp, philo->n, str);
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
