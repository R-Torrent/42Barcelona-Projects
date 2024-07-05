/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:12:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/05 16:28:18 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_sems_philos(t_data *pdata, pid_t *pid_last, int error)
{
	int		i;
	pid_t	*pid;

	i = 0;
	while (i < NUMBS)
	{
		if (pdata->sem[i] != SEM_FAILED)
			error = (sem_close(pdata->sem[i]) || error);
		i++;
	}
	pid = pdata->pid;
	while (pid < pid_last)
		error = (kill(*pid++, SIGTERM) || error);
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct s_philo	philo;
	struct s_contrl	contrl;
	pid_t			child_pid;
	int				i;

	data.philo = &philo;
	philo.contrl = &contrl;
	contrl.pdata = &data;
	i = 0;
	if (!load_sim(&data, --argc, ++argv))
	{
		while (i < data.number_of_philos)
		{
			data.philo->n = i + 1;
			child_pid = fork();
			if (child_pid == -1)
				break ;
			else if (!child_pid)
				run_philo(data.philo);
			data.pid[i++] = child_pid;
		}
		if (i == data.number_of_philos)
			sem_post(data.sem[MASTR]);
	}
	destroy_sems_philos(&data, data.pid + i, i < data.number_of_philos);
	free(data.sem);
	free(data.pid);
	return (data.exit_status);
}
