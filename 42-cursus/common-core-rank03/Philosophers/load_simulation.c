/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:48:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/26 13:31:26 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_philos(struct s_data *pdata, pthread_t *last)
{
	pthread_t	*philo;

	destroy_forks(pdata, pdata->fork + pdata->number_of_philosophers, 1);
	philo = pdata->philo;
	while (philo < last)
		pthread_detach(*philo++);
}

static void	create_forks_n_philos(struct s_data *pdata)
{
	pthread_t		*philo;
	pthread_mutex_t	*fork;
	struct s_args	*args;
	int				i;

	fork = pdata->fork + pdata->number_of_philosophers;
	args = pdata->args + pdata->number_of_philosophers;
	while ((fork--, args) > pdata->args && !pdata->exit_status)
	{
		i = args-- - pdata->args;
		args->pdata = pdata;
		args->nphilo = i;
		if (pthread_mutex_init(fork, NULL))
			destroy_forks(pdata, fork, 1);
		else
			pthread_mutex_lock(fork);
	}
	philo = pdata->philo + pdata->number_of_philosophers;
	args = pdata->args + pdata->number_of_philosophers;
	while ((philo--, args--) > pdata->args && !pdata->exit_status)
		if (pthread_create(philo, NULL, (void *(*)(void *))run_sim, args))
			destroy_philos(pdata, philo);
}

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

int	load_sim(struct s_data *pdata, int param, char **args)
{
	const int		check_args = param < 4 || param > 5
		|| atoi3(*args++, &pdata->number_of_philosophers, 1)
		|| atoi3(*args++, &pdata->time_to_die, 0)
		|| atoi3(*args++, &pdata->time_to_eat, 0)
		|| atoi3(*args++, &pdata->time_to_sleep, 0)
		|| (param == 5
			&& atoi3(*args, &pdata->number_of_times_each_philosopher_must_eat,
				0));

	pdata->philo = malloc(pdata->number_of_philosophers * sizeof(pthread_t));
	pdata->fork = malloc(pdata->number_of_philosophers
			* sizeof(pthread_mutex_t));
	pdata->args = malloc(pdata->number_of_philosophers * sizeof(struct s_args));
	pdata->exit_status = (check_args || !pdata->philo || !pdata->fork
			|| !pdata->args);
	if (!pdata->exit_status)
		create_forks_n_philos(pdata);
	return (pdata->exit_status);
}
