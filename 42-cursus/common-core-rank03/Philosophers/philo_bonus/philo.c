/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:12:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/30 12:37:32 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	struct s_contrl	contrl;

	data.contrl = &contrl;
	if (!load_sim(&data, --argc, ++argv))
	{
		data.exit_status = (pthread_join(contrl.thread, NULL)
				|| contrl.flags & PHILO_ERR);
		destroy_locks(&data, data.fork, 0);
	}
	free(data.sem);
	free(data.philo);
	return (data.exit_status);
}
