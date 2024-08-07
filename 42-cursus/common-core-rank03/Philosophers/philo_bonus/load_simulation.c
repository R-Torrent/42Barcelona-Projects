/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:48:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/07 14:23:19 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	create_sems(t_data *pdata)
{
	const char		*locations[] = {"/MASTR", "/PRINT", "/FORKS", "/MLSOK",
		"/TERMN"};
	int				i;
	int				j;

	pdata->shared_sems[MASTR] = sem_open(locations[MASTR], S_OFLAG, S_MODE, 0);
	pdata->shared_sems[PRINT] = sem_open(locations[PRINT], S_OFLAG, S_MODE, 1);
	pdata->shared_sems[FORKS] = sem_open(locations[FORKS], S_OFLAG, S_MODE,
			pdata->number_of_philos);
	pdata->shared_sems[MLSOK] = sem_open(locations[MLSOK], S_OFLAG, S_MODE, 0);
	pdata->shared_sems[TERMN] = sem_open(locations[TERMN], S_OFLAG, S_MODE, 0);
	i = 0;
	j = 0;
	while (i < NUMBS)
	{
		if (pdata->shared_sems[i] != SEM_FAILED && !sem_unlink(locations[i]))
			j++;
		i++;
	}
	return (j < NUMBS);
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
	int			t;
	const int	check_args = params < 4 || params > 5
		|| atoi4(*args++, &pdata->number_of_philos, 1, 1)
		|| atoi4(*args++, (int *)&pdata->time_to_die, 0, 1000)
		|| atoi4(*args++, (int *)&pdata->time_to_eat, 0, 1000)
		|| atoi4(*args++, (int *)&pdata->time_to_sleep, 0, 1000)
		|| (params == 5 && atoi4(*args, &pdata->philo->meals_left, 0, 1));

	if (params != 5)
		pdata->philo->meals_left = -1;
	pdata->philo->last_meal = 0;
	t = SLEEP_N_THINK + (int)pdata->time_to_eat - (int)pdata->time_to_sleep;
	if (t > 0)
		pdata->time_to_think = (unsigned int)t;
	else
		pdata->time_to_think = 0;
	pdata->philo->contrl->timestamp[0] = '0';
	pdata->philo->contrl->timestamp[1] = '\0';
	pdata->philo->contrl->elapsed = 0;
	pdata->philo->contrl->err = 0;
	pdata->pid = malloc(pdata->number_of_philos * sizeof(pid_t));
	pdata->exit_status = (create_sems(pdata) || check_args || !pdata->pid);
	return (pdata->exit_status);
}
