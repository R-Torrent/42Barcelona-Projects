/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:12:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/06/30 23:47:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_sems_philos(t_data *pdata, t_philo *philo, int error)
{
	t_philo *const	lastp = pdata->philo + pdata->number_of_philos;

	if (pdata->sem[MASTR] != SEM_FAILED) {
		error = (sem_close(pdata->sem[MASTR]) || error);
		error = (sem_unlink(SEM_MASTR) || error);
	}
	if (pdata->sem[FORKS] != SEM_FAILED) {
		error = (sem_close(pdata->sem[FORKS]) || error);
		error = (sem_unlink(SEM_FORKS) || error);
	}
	while (philo < lastp)
		error = (kill(philo++->pid, SIGTERM) || error);
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	t_data	data;

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
