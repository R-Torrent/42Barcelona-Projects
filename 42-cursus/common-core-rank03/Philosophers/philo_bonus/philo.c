/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:12:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/02 00:16:26 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_sems_philos(t_data *pdata, pid_t *pid_last, int error)
{
	pid_t	*pid;

	pid = pdata->pid;
	if (pdata->sem[MASTR] != SEM_FAILED)
	{
		error = (sem_close(pdata->sem[MASTR]) || error);
		error = (sem_unlink(SEM_MASTR) || error);
	}
	if (pdata->sem[FORKS] != SEM_FAILED)
	{
		error = (sem_close(pdata->sem[FORKS]) || error);
		error = (sem_unlink(SEM_FORKS) || error);
	}
	while (pid < lastp)
		error = (kill(pid++, SIGTERM) || error);
	pdata->exit_status = (pdata->exit_status || error);
}

static int	create_sems_philos(t_data *pdata)
{
	int		i;
	pid_t	child_pid;

	pdata->sem[MASTR] = sem_open(SEM_MASTR, O_CREAT | O_RDWR,
			S_IRUSR | S_IWUSR, 0);
	pdata->sem[FORKS] = sem_open(SEM_FORKS, O_CREAT | O_RDWR,
			S_IRUSR | S_IWUSR, pdata->number_of_philos);
	i = 0;
	while (i < pdata->number_of_philos)
	{
		pdata->philo->n = i + 1;
		child_pid = fork();
		if (child_pid == -1)
			break ;
		if (!child_pid)
			run_philo(philo);
		pdata->pid[i++] = child_pid;
	}
	if (i < pdata->number_of_philos || pdata->sem[MASTR] == SEM_FAILED
		|| pdata->sem[FORKS] == SEM_FAILED)
		destroy_sems_philos(pdata, pdata->pid + i, 1);
	return (pdata->exit_status);
}

// variation on the atoi lib function, it returns an error flag, with two extra
// arguments: 'min' minimum valid input, 'scale' to multiply answer by
static int	atoi4(const char *str, int *n, int min, int scale)
{
	int	i;
	int	sg;

	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	sg = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	*n = 0;
	while ('0' <= *str && *str <= '9')
	{
		i = *str++ - '0';
		if ((sg && *n < (INT_MIN + i) / 10) || (!sg && *n > (INT_MAX - i) / 10))
			return (1);
		if (sg)
			*n = 10 * *n - i;
		else
			*n = 10 * *n + i;
	}
	if (*str || *n < min)
		return (1);
	*n *= scale;
	return (0);
}

int	load_sim(t_data *pdata, int params, char **args)
{
	const int	check_args = params < 4 || params > 5
		|| atoi4(*args++, &pdata->number_of_philos, 1, 1)
		|| atoi4(*args++, (int *)&pdata->time_to_die, 0, 1000)
		|| atoi4(*args++, (int *)&pdata->time_to_eat, 0, 1000)
		|| atoi4(*args++, (int *)&pdata->time_to_sleep, 0, 1000)
		|| (params == 5 && atoi4(*args, &pdata->philo->meals_left, 0, 1));
	const int	tthink = SLEEP_N_THINK + (int)pdata->time_to_eat
		- (int)pdata->time_to_sleep;

	if (params != 5)
		pdata->philo->meals_left = -1;
	pdata->philo->last_meal = 0;
	pdata->philo->flags = PHILO__OK;
	if (!pdata->philo->meals_left)
		pdata->philo->flags |= MEALS__OK;
	pdata->time_to_think = 0;
	if (tthink > 0)
		pdata->time_to_think = (unsigned int)tthink;
	pdata->contrl->timestamp[0] = '0';
	pdata->contrl->elapsed = 0;
	pdata->sem = malloc(2 * sizeof(sem_t *));
	pdata->pid = malloc(pdata->number_of_philos * sizeof(pid_t));
	pdata->exit_status = (check_args || !pdata->sem || !pdata->pid
			|| create_sems_philos(pdata) || sem_post(pdata->sem[MASTR]));
	return (pdata->exit_status);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct s_philo	philo;
	struct s_contrl	contrl;

	data.philo = &philo;
	philo.contrl = &contrl;
	contrl.pdata = &data;
	if (!load_sim(&data, --argc, ++argv))
	{
		data.exit_status = (pthread_join(contrl.thread, NULL)
				|| contrl.flags & PHILO_ERR);
		destroy_sems_philos(&data, data.pid + data.number_of_philos, 0);
	}
	free(data.sem);
	free(data.pid);
	return (data.exit_status);
}
