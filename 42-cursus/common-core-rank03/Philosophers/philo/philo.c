/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/21 15:50:56 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NOTE: Error analysis is suspended for the 'pthread_mutex_destroy' calls to
// the fork mutexes. These calls are made from the main thread, not the actual
// holders of the lock--which are frozen in place grasping at one fork as they
// wait for the second fork to be freed--. As such, the behaviour here of the
// 'pthread_mutex_destroy' function is undefined.
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
		pthread_mutex_destroy(&fork++->lock);
	philo = pdata->philo;
	while (philo < lastp)
		error = (pthread_mutex_destroy(&philo++->access) || error);
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct s_contrl	contrl;
	struct s_philo	*pphilo;

	data.number_of_philos = 0;
	data.contrl = &contrl;
	if (!load_sim(&data, --argc, ++argv))
	{
		data.exit_status = (pthread_join(contrl.thread, NULL)
				|| contrl.flags & PHILO_ERR);
		pphilo = data.philo;
		while (pphilo - data.philo < data.number_of_philos)
			data.exit_status = (pthread_join(pphilo++->thread, NULL)
					|| data.exit_status);
		destroy_locks(&data, data.fork, 0);
	}
	free(data.shared_locks);
	free(data.fork);
	free(data.philo);
	return (data.exit_status);
}
