/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:48:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/11 22:49:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks_philos(t_data *pdata)
{
	struct s_fork	*fork;
	struct s_philo	*philo;

	fork = pdata->fork + pdata->number_of_philos;
	philo = pdata->philo + pdata->number_of_philos;
	while ((fork--, philo--) > pdata->philo)
	{
		if (pthread_mutex_init(&fork->lock, NULL))
			break ;
		else if (pthread_create(&philo->thread, NULL,
				(void *)run_philo, philo))
		{
			while (++philo < pdata->philo + pdata->number_of_philos)
				pthread_detach(philo->thread);
			fork--;
			break ;
		}
	}
	if (philo >= pdata->philo)
		destroy_locks(pdata, ++fork, 1);
	return (pdata->exit_status);
}

static int	create_locks(t_data *pdata)
{
	int	i;
	int	j;

	i = NUMBER_OF_LOCKS;
	while (i-- > 0)
		if (pthread_mutex_init(pdata->shared_locks + i, NULL))
			break ;
	j = pdata->number_of_philos;
	while (j-- > 0)
		if (pthread_mutex_init(&pdata->philo[j].access, NULL))
			break ;
	pdata->exit_status = (i != -1 || j != -1
			|| pthread_mutex_lock(&pdata->shared_locks[MASTER_LOCK]));
	if (pdata->exit_status)
	{
		while (++i < NUMBER_OF_LOCKS)
			pthread_mutex_destroy(pdata->shared_locks + i);
		while (++j < pdata->number_of_philos)
			pthread_mutex_destroy(&pdata->philo[j].access);
	}
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
	memset(pdata->fork, 0, pdata->number_of_philos * sizeof(t_fork));
	memset(pdata->philo, 0, pdata->number_of_philos * sizeof(t_philo));
	i = 0;
	while (i < pdata->number_of_philos)
	{
		pdata->fork[i].n = i + 1;
		pdata->philo[i].meals_left = times_each_philo_must_eat;
		if (!times_each_philo_must_eat)
			pdata->philo[i].flags |= MEALS__OK;
		pdata->philo[i].n = i + 1;
		pdata->philo[i].fork[LEFT] = pdata->fork + i;
		pdata->philo[i].fork[RIGHT] = pdata->fork
			+ (i + 1) % pdata->number_of_philos;
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
	pdata->shared_locks = malloc(NUMBER_OF_LOCKS * sizeof(pthread_mutex_t));
	pdata->fork = malloc(pdata->number_of_philos * sizeof(t_fork));
	pdata->philo = malloc(pdata->number_of_philos * sizeof(t_philo));
	pdata->exit_status = (check_args || !pdata->shared_locks || !pdata->fork
			|| !pdata->philo);
	if (!pdata->exit_status)
	{
		init_data(pdata, times_each_philo_must_eat);
		pdata->exit_status = (create_locks(pdata) || create_forks_philos(pdata)
				|| pthread_create(&pdata->contrl->thread, NULL,
					(void *)run_contrl, pdata)
				|| pthread_mutex_unlock(&pdata->shared_locks[MASTER_LOCK]));
	}
	return (pdata->exit_status);
}
