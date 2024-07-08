/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:12:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/09 00:38:44 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*run_cleaner(t_data *pdata)
{
	sem_t		*sem;
	int *const	err = &pdata->exit_status;

	sem = *pdata->sem;
	*err = (sem_wait(pdata->sem[TERMN]) || *err);
	*err = (sem_post(pdata->sem[TERMN]) || *err);
	while (sem - *pdata->sem < NUMBS)
	{
		*err = ((sem != SEM_FAILED && sem_close(sem)) || *err);
		sem++;
	}
	free(pdata->sem);
	return (NULL);
}

void	destroy_sems_philos(t_data *pdata, pid_t *pid_last, int *err)
{
	pid_t	*pid;

	if (*err)
		sem_post(pdata->sem[TERMN]);
	run_cleaner(pdata);
	pid = pdata->pid;
	while (pid < pid_last)
		*err = (waitpid(*pid++, NULL, 0) == -1 || *err);
	free(pdata->pid);
}

void	*run_terminator(t_data *pdata)
{
	pdata->exit_status = (sem_wait(pdata->sem[MLSOK])
			|| sem_post(pdata->sem[TERMN]));
	return (NULL);
}

void	spawn_philos(t_data *pdata, int *i)
{
	pid_t	child_pid;

	while (*i < pdata->number_of_philos)
	{
		pdata->philo->n = *i + 1;
		child_pid = fork();
		if (child_pid == -1)
			break ;
		else if (!child_pid)
		{
			free(pdata->pid);
			run_philo(pdata->philo);
		}
		pdata->pid[(*i)++] = child_pid;
	}
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct s_philo	philo;
	struct s_contrl	contrl;
	int				i;

	data.philo = &philo;
	philo.contrl = &contrl;
	contrl.pdata = &data;
	i = 0;
	if (!load_sim(&data, --argc, ++argv))
	{
		spawn_philos(&data, &i);
		data.exit_status = (i != data.number_of_philos
				|| pthread_create(&data.terminator, NULL,
					(void *(*)(void *))run_terminator, &data)
				|| pthread_detach(data.terminator)
				|| sem_post(data.sem[MASTR]));
	}
	destroy_sems_philos(&data, data.pid + i, &data.exit_status);
	return (data.exit_status);
}
