/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:12:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/14 20:17:22 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	run_cleaner(t_data *pdata)
{
	sem_t		*sem;
	int *const	err = &pdata->exit_status;

	sem = *pdata->shared_sems;
	*err = (*err || sem_wait(pdata->shared_sems[TERMN])
			|| sem_post(pdata->shared_sems[TERMN]));
	while (sem - *pdata->shared_sems < NUMBS)
	{
		*err = ((sem != SEM_FAILED && sem_close(sem)) || *err);
		sem++;
	}
	if (pdata->shared_sems)
		free(pdata->shared_sems);
}

static void	destroy_sems_philos(t_data *pdata, pid_t *pid_last, int *err)
{
	pid_t	*pid;

	if (pdata->shared_sems[TERMN] != SEM_FAILED)
		sem_post(pdata->shared_sems[TERMN]);
	run_cleaner(pdata);
	pid = pdata->pid;
	while (pid < pid_last)
		*err = (waitpid(*pid++, NULL, 0) == -1 || *err);
	if (pdata->pid)
		free(pdata->pid);
}

static void	run_terminator(t_data *pdata)
{
	int	meals_ok;

	meals_ok = pdata->number_of_philos;
	while (meals_ok-- && !pdata->exit_status)
		pdata->exit_status = sem_wait(pdata->shared_sems[MLSOK]);
	pdata->exit_status = (sem_post(pdata->shared_sems[TERMN])
			|| pdata->exit_status);
}

static void	spawn_philos(t_data *pdata, int *i)
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
					(void *)run_terminator, &data)
				|| pthread_detach(data.terminator)
				|| sem_post(data.shared_sems[MASTR])
				|| sem_wait(data.shared_sems[TERMN]));
	}
	destroy_sems_philos(&data, data.pid + i, &data.exit_status);
	return (data.exit_status);
}
