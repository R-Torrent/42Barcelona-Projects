/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:48:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/31 01:06:25 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	detach_philos(t_data *pdata, t_fork *fork, t_philo *philo)
{
	t_philo *const	last = pdata->philo + pdata->number_of_philos;

	destroy_forks(pdata, fork, 1);
	while (philo < last)
		pthread_detach(philo++->thread);
}

static int	create_forks_n_philos(t_data *pdata)
{
	struct s_fork	*fork;
	struct s_philo	*philo;
	struct s_args	*args;

	fork = pdata->fork + pdata->number_of_philos;
	philo = pdata->philo + pdata->number_of_philos;
	args = pdata->philo_args + pdata->number_of_philos;
	if (pthread_mutex_lock(pdata->forks_locked))
		destroy_forks(pdata, fork, 1);
	while ((fork--, philo--, args--) > pdata->philo_args && !pdata->exit_status)
	{
		args->pdata = pdata;
		args->n = philo->n;
		if (pthread_mutex_init(&fork->lock, NULL))
			destroy_forks(pdata, ++fork, 1);
		else if (pthread_create(&philo->thread, NULL,
				(void *(*)(void *))run_philo, args))
			detach_philos(pdata, fork, ++philo);
	}
	if (!pdata->exit_status && pthread_mutex_unlock(pdata->forks_locked))
		destroy_forks(pdata, ++fork, 1);
	return (!pdata->exit_status);
}

// variation on the atoi lib function, it returns an error flag,
// with extra argument 'minimum' valid input
static int	atoi3(const char *str, int *n, int min)
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
	return (0);
}

static int	init_data(t_data *pdata, int times_each_philo_must_eat)
{
	int	i;

	if (!pdata->exit_status)
	{
		pdata->time_to_die *= 1000U;
		pdata->time_to_eat *= 1000U;
		pdata->time_to_sleep *= 1000U;
		memset(pdata->fork, 0, pdata->number_of_philos * sizeof(t_fork));
		memset(pdata->philo, 0, pdata->number_of_philos * sizeof(t_philo));
		i = 0;
		while (i < pdata->number_of_philos)
		{
			pdata->fork[i].n = i + 1;
			pdata->philo[i].meals_left = times_each_philo_must_eat;
			pdata->philo[i].n = i + 1;
			pdata->philo[i].fork[LEFT] = pdata->fork + i;
			pdata->philo[i].fork[RIGHT] = pdata->fork
				+ ++i % pdata->number_of_philos;
		}
		pdata->exit_status = (phtread_mutex_init(pdata->forks_locked, NULL)
				|| gettimeofday(pdata->t0, NULL));
	}
	return (pdata->exit_status);
}

int	load_sim(t_data *pdata, int params, char **args)
{
	int			times_each_philo_must_eat;
	const int	check_args = params < 4 || params > 5
		|| atoi3(*args++, &pdata->number_of_philos, 1)
		|| atoi3(*args++, (int *)&pdata->time_to_die, 0)
		|| atoi3(*args++, (int *)&pdata->time_to_eat, 0)
		|| atoi3(*args++, (int *)&pdata->time_to_sleep, 0)
		|| (params == 5 && atoi3(*args, &times_each_philo_must_eat, 0));

	if (params != 5)
		times_each_philo_must_eat = -1;
	pdata->fork = malloc(pdata->number_of_philos * sizeof(t_fork));
	pdata->philo = malloc(pdata->number_of_philos * sizeof(t_philo));
	pdata->philo_args = malloc(pdata->number_of_philos * sizeof(struct s_args));
	pdata->exit_status = (check_args || !pdata->fork || !pdata->philo
			|| !pdata->philo_args);
	if (!init_data(pdata, times_each_philo_must_eat))
		create_forks_n_philos(pdata);
	return (!pdata->exit_status);
}
