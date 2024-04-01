/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:48:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/01 20:46:42 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_forks_n_philos(t_data *pdata)
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
				(void *(*)(void *))run_philo, philo))
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

	i = 0;
	while (i < NUMBER_OF_LOCKS)
	{
		if (pthread_mutex_init(pdata->shared_locks + i, NULL))
			break ;
		i++;
	}
	pdata->exit_status = (i != NUMBER_OF_LOCKS
			|| pthread_mutex_lock(&pdata->shared_locks[INIT_SIM]));
	if (pdata->exit_status)
		while (i >= 0)
			pthread_mutex_destroy(pdata->shared_locks + --i);
	return (pdata->exit_status);
}

static void	init_data(t_data *pdata, int times_each_philo_must_eat)
{
	int	i;

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
		if (!times_each_philo_must_eat)
			pdata->philo[i].flags |= MEALS__OK;
		pdata->philo[i].n = i + 1;
		pdata->philo[i].fork[LEFT] = pdata->fork + i;
		pdata->philo[i].fork[RIGHT] = pdata->fork
			+ (i + 1) % pdata->number_of_philos;
		pdata->philo[i].pdata = pdata;
		i++;
	}
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
	pdata->shared_locks = malloc(NUMBER_OF_LOCKS * sizeof(pthread_mutex_t));
	pdata->fork = malloc(pdata->number_of_philos * sizeof(t_fork));
	pdata->philo = malloc(pdata->number_of_philos * sizeof(t_philo));
	pdata->exit_status = (check_args || !pdata->shared_locks || !pdata->fork
			|| !pdata->philo);
	if (!pdata->exit_status)
	{
		init_data(pdata, times_each_philo_must_eat);
		pdata->exit_status = (create_locks(pdata) || create_forks_n_philos(pdata)
				|| gettimeofday(pdata->t0, NULL)
				|| pthread_mutex_unlock(&pdata->shared_locks[INIT_SIM]));
	}
	return (pdata->exit_status);
}
