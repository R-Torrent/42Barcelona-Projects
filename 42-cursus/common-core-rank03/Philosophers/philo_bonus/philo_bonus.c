/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:12:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/31 10:13:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	destroy_shared_sems(t_data *pdata)
{
	sem_t	**sem;
	int		err;

	sem = pdata->shared_sems;
	err = 0;
	while (sem - pdata->shared_sems < NUMBS)
	{
		err = (*sem == SEM_FAILED || sem_close(*sem) || err);
		sem++;
	}
	return (err);
}

static void	destroy_sems_philos(t_data *pdata, pid_t *pid_last, int *err)
{
	pid_t	*pid;
	int		wstatus;

	if (pdata->shared_sems[TERMN] != SEM_FAILED)
		*err = (sem_post(pdata->shared_sems[TERMN]) || *err);
	pid = pdata->pid;
	while (pid < pid_last)
		*err = (waitpid(*pid++, &wstatus, 0) == -1 || !WIFEXITED(wstatus)
				|| WEXITSTATUS(wstatus) || *err);
	free(pdata->pid);
	*err = (pthread_join(pdata->terminator, NULL) || destroy_shared_sems(pdata)
			|| *err);
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
	t_philo *const	philo = pdata->philo;
	pid_t			child_pid;
	int				err;

	while (*i < pdata->number_of_philos)
	{
		philo->n = *i + 1;
		child_pid = fork();
		if (child_pid == -1)
			break ;
		else if (!child_pid)
		{
			free(pdata->pid);
			err = (load_philo(philo) || philo->contrl->ret & PHILO_ERR);
			err = (sem_post(pdata->shared_sems[MLSOK]) || err);
			err = (philo->access == SEM_FAILED
					|| sem_close(philo->access) || err);
			err = (philo->read_time == SEM_FAILED
					|| sem_close(philo->read_time) || err);
			exit(destroy_shared_sems(philo->contrl->pdata) || err);
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

	data.number_of_philos = 0;
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
				|| sem_post(data.shared_sems[MASTR])
				|| sem_wait(data.shared_sems[TERMN]));
	}
	destroy_sems_philos(&data, data.pid + i, &data.exit_status);
	return (data.exit_status);
}
