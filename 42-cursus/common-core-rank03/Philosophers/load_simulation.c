/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:48:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/30 14:05:15 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	*run(struct s_args *philo_args)
{
	t_data *const	pdata = philo_args->pdata;
	const int		nphilo = philo_args->nphilo;
	const int		nforks[2] = {nphilo - 1, nphilo % pdata->number_of_philos};
	int *const		philo_exit = pdata->philo_result + nphilo - 1;
	char			timestamp[12];

	while (!*philo_exit)
		*philo_exit = (think(pdata, nphilo, timestamp)
				|| pick_forks(pdata, nphilo, nforks, timestamp)
				|| eat(pdata, nphilo, timestamp)
				|| drop_forks(pdata, nphilo, nforks, timestamp)
				|| sleep(pdata, nphilo, timestamp));
	return (NULL);
}

static void	detch_philos(t_data *pdata, pthread_mutex_t *fork, pthread_t *philo)
{
	pthread_t *const	last = pdata->pdata->philo + pdata->number_of_philos;

	destroy_forks(pdata, fork, 1);
	while (philo < last)
		pthread_detach(*philo++);
}

static int	create_forks_n_philos(t_data *pdata)
{
	pthread_mutex_t	*fork;
	pthread_t		*philo;
	struct s_args	*args;
	int				i;

	pdata->exit_status = phtread_mutex_init(pdata->forks_locked, NULL));
	fork = pdata->fork + pdata->number_of_philos;
	philo = pdata->philo + pdata->number_of_philos;
	args = pdata->philo_args + pdata->number_of_philos;
	if (!pdata->exit_status && pthread_mutex_lock(pdata->forks_locked))
		destroy_forks(pdata, fork, 1);
	while ((fork--, philo--, args) > pdata->philo_args && !pdata->exit_status)
	{
		i = args-- - pdata->philo_args;
		args->pdata = pdata;
		args->nphilo = i;
		if (pthread_mutex_init(fork, NULL))
			destroy_forks(pdata, ++fork, 1);
		else if (pthread_create(philo, NULL, (void *(*)(void *))run, args))
			detch_philos(pdata, fork, ++philo);
	}
	if (!pdata->exit_status && pthread_mutex_unlock(pdata->forks_locked))
		destroy_forks(pdata, fork, 1);
	return (!pdata->exit_status);
}

// variation on the atoi lib function, it returns an error flag,
// with extra argument 'minimum' valid input
static int	atoi3(const char *str, int *n, const int min)
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

int	load(t_data *pdata, int params, char **args)
{
	const int	check_args = params < 4 || params > 5
		|| atoi3(*args++, &pdata->number_of_philos, 1)
		|| atoi3(*args++, (int *)&pdata->time_to_die, 0)
		|| atoi3(*args++, (int *)&pdata->time_to_eat, 0)
		|| atoi3(*args++, (int *)&pdata->time_to_sleep, 0)
		|| (params == 5 && atoi3(*args,
				&pdata->number_of_times_each_philo_must_eat, 0))
		|| gettimeofday(pdata->t0, NULL);

	pdata->fork = malloc(pdata->number_of_philos * sizeof(pthread_mutex_t));
	pdata->fork_held = malloc(pdata->number_of_philos * sizeof(int));
	pdata->philo = malloc(pdata->number_of_philos * sizeof(pthread_t));
	pdata->philo_args = malloc(pdata->number_of_philos * sizeof(struct s_args));
	pdata->philo_result = malloc(pdata->number_of_philos * sizeof(int));
	pdata->exit_status = (check_args || !pdata->fork || !pdata->fork_held
			|| !pdata->philo || !pdata->philo_args || !pdata->philo_result);
	if (!pdata->exit_status && create_forks_n_philos(pdata))
	{
		pdata->time_to_die *= 1000U;
		pdata->time_to_eat *= 1000U;
		pdata->time_to_sleep *= 1000U;
		memset(pdata->fork_held, 0, pdata->number_of_philos * sizeof(int));
		memset(pdata->philo_result, 0, pdata->number_of_philos * sizeof(int));
	}
	return (!pdata->exit_status);
}
