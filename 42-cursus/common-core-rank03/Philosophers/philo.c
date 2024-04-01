/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/01 02:35:28 by rtorrent         ###   ########.fr       */
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

static char	*tstamp(char *timestamp, unsigned int *dst,
		const struct timeval *t0, const struct timeval *t)
{
	char *const	timestamp0 = timestamp;
	long		elapsed;

	elapsed = (long)(t->tv_sec - t0->tv_sec) * 1000L
		+ (long)(t->tv_usec - t0->tv_usec) / 1000L;
	if (dst)
		*dst = (unsigned int)elapsed;
	if (elapsed < 0)
		*timestamp++ = '-';
	place_digit(elapsed, &timestamp);
	*timestamp = '\0';
	return (timestamp0);
}

int	print_stamp(unsigned int *dst, const struct timeval *t0, int n,
		const char *str)
{
	struct timeval	t;
	const int		error_status = gettimeofday(&t, NULL);
	char			timestamp[12];

	if (!error_status)
		printf("%s %i %s\n", tstamp(timestamp, dst, t0, &t), n, str);
	return (error_status);
}

int	destroy_forks(t_data *pdata, t_fork *fork, int error)
{
	t_fork *const	last = pdata->fork + pdata->number_of_philos;
	int				i;

	if (error)
		pthread_mutex_unlock(&pdata->shared_locks[FORK_PICKING]);
	i = 0;
	while (i < NUMBER_OF_LOCKS)
		error = (pthread_mutex_destroy(pdata->shared_locks + i++) || error);
	while (fork < last)
		error = (pthread_mutex_destroy(&fork++->lock) || error);
	pdata->exit_status = (pdata->exit_status || error);
	return (pdata->exit_status);
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
