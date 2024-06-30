/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:33:46 by rtorrent          #+#    #+#             */
/*   Updated: 2024/06/30 23:51:26 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_sems_philos(t_data *pdata)
{
	t_philo	*philo;
	pid_t	child_pid;

	pdata->sem[MASTR] = sem_open(SEM_MASTR, O_CREAT | O_RDWR,
			S_IRUSR | S_IWUSR, 0);
	pdata->sem[FORKS] = sem_open(SEM_FORKS, O_CREAT | O_RDWR,
			S_IRUSR | S_IWUSR, pdata->number_of_philos);
	philo = pdata->philo + pdata->number_of_philos;
	if (pdata->sem[MASTR] == SEM_FAILED || pdata->sem[FORKS] == SEM_FAILED)
		philo--;
	else
	{
		while (philo-- > pdata->philo)
		{
			child_pid = fork();
			if (child_pid == -1)
				break ;
			if (!child_pid)
				run_philo(philo);
			philo->pid = child_pid;
		}
	}
	if (++philo > pdata->philo)
		destroy_sems_philos(pdata, philo, 1);
	return (pdata->exit_status);
}

static void	init_data(t_data *pdata, int times_each_philo_must_eat)
{
	int	i;

	i = SLEEP_N_THINK + (int)pdata->time_to_eat - (int)pdata->time_to_sleep;
	if (i > 0)
		pdata->time_to_think = (unsigned int)i;
	else
		pdata->time_to_think = 0;
	memset(pdata->philo, 0, pdata->number_of_philos * sizeof(t_philo));
	i = 0;
	while (i < pdata->number_of_philos)
	{
		pdata->philo[i].meals_left = times_each_philo_must_eat;
		if (!times_each_philo_must_eat)
			pdata->philo[i].flags |= MEALS__OK;
		pdata->philo[i].n = i + 1;
		pdata->philo[i++].pdata = pdata;
	}
	memset(pdata->contrl, 0, sizeof(t_contrl));
	*pdata->contrl->timestamp = '0';
	pdata->contrl->pdata = pdata;
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
	int			times_each_philo_must_eat;
	const int	check_args = params < 4 || params > 5
		|| atoi4(*args++, &pdata->number_of_philos, 1, 1)
		|| atoi4(*args++, (int *)&pdata->time_to_die, 0, 1000)
		|| atoi4(*args++, (int *)&pdata->time_to_eat, 0, 1000)
		|| atoi4(*args++, (int *)&pdata->time_to_sleep, 0, 1000)
		|| (params == 5 && atoi4(*args, &times_each_philo_must_eat, 0, 1));

	if (params != 5)
		times_each_philo_must_eat = -1;
	pdata->sem = malloc(2 * sizeof(sem_t *));
	pdata->philo = malloc(pdata->number_of_philos * sizeof(t_philo));
	pdata->exit_status = (check_args || !pdata->sem || !pdata->philo);
	if (!pdata->exit_status)
	{
		init_data(pdata, times_each_philo_must_eat);
		pdata->exit_status = (create_sems_philos(pdata)
				|| sem_post(pdata->sem[MASTR]));
	}
	return (pdata->exit_status);
}
