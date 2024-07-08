/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:12:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/08 02:04:24 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_cleaner(t_data *pdata)
{
	int			i;
	int *const	err = &pdata->exit_status;

	i = 0;
	*err = (sem_wait(pdata->sem[TERMN]) || *err);
	*err = (sem_post(pdata->sem[TERMN]) || *err);
	while (i < NUMBS)
	{
		*err = ((pdata->sem[i] != SEM_FAILED && sem_close(pdata->sem[i]))
				|| *err);
		i++;
	}
	free(pdata->sem);
	return (NULL);
}

void	destroy_sems_philos(t_data *pdata, pid_t *pid_last, int error)
{
	pid_t	*pid;

	run_cleaner(pdata);
	pid = pdata->pid;
	while (pid < pid_last)
		error = (kill(*pid++, SIGTERM) || error);
	free(pdata->pid);
	pdata->exit_status = (pdata->exit_status || error);
}

void	*run_terminator(t_data *pdata)
{
	pdata->exit_status = (sem_wait(pdata->sem[MLSOK])
			|| sem_post(pdata->sem[TERMN]));
	return (NULL);
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
		data.exit_status = (i != data.number_of_philos
				|| pthread_create(&data.terminator, NULL,
					(void *(*)(void *))run_terminator, &data)
				|| pthread_detach(data.terminator)
				|| sem_post(data.sem[MASTR]));
	}
	destroy_sems_philos(&data, data.pid + i, i < data.number_of_philos);
	return (data.exit_status);
}
