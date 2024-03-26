/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/26 13:28:33 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_sim(struct s_args *args)
{
	struct s_data *const	pdata = args->pdata;
	const int				nphilo = args->nphilo;

	printf("Thread: %ld, philo: %d\n", (long)pdata->philo[nphilo - 1], nphilo);
	return (NULL);
}

void	destroy_forks(struct s_data *pdata, pthread_mutex_t *last, int error)
{
	pthread_mutex_t	*fork;

	fork = pdata->fork;
	while (fork < last)
	{
		error = (pthread_mutex_unlock(fork) || error);
		error = (pthread_mutex_destroy(fork++) || error);
	}
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct timeval	tstart;
	pthread_t		*philo;

	if (!load_sim(&data, --argc, ++argv))
	{
		if (!gettimeofday(&tstart, NULL))
		{
			philo = data.philo + data.number_of_philosophers;
			while (philo-- > data.philo)
				pthread_join(*philo, NULL);
		}
		destroy_forks(&data, data.fork + data.number_of_philosophers, 0);
	}
	free(data.fork);
	free(data.philo);
	free(data.args);
	return (data.exit_status);
}
