/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/25 18:56:24 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(struct s_data *pdata, pthread_mutex_t *last, int error)
{
	pthread_mutex_t	*fork;

	if (pdata->fork)
	{
		fork = pdata->fork;
		while (fork < last)
			error = (error || pthread_mutex_destroy(fork++));
	}
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	struct timeval	tstart;
	struct s_data	data;

	if (gettimeofday(&tstart, NULL))
		return (1);
	if (!load_sim(&data, --argc, ++argv))
	{
		printf("Hello!\n");
		destroy_forks(&data, data.fork + data.number_of_philosophers, 0);
	}
	free(data.fork);
	free(data.philo);
	return (data.exit_status);
}
