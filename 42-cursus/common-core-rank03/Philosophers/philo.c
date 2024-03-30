/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/30 01:06:56 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*tstamp(char *timestamp, struct timeval *t0, struct timeval *t)
{
// ***** CONTINUE WITH THIS!!
	return (timestamp);
}

void	destroy_forks(t_data *pdata, pthread_mutex_t *fork, int error)
{
	pthread_mutex_t *const	last = pdata->fork + pdata->number_of_philos;

	error = (pthread_mutex_destroy(pdata->forks_locked) || error);
	while (fork < last)
		error = (pthread_mutex_destroy(fork++) || error);
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct timeval	t0;
	pthread_t		*philo;
	int				*philo_result;

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
	free(data.fork_held);
	free(data.philo);
	free(data.philo_args);
	free(data.philo_result);
	return (data.exit_status);
}
