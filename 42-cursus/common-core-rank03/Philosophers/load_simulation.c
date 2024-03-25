/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:48:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/25 19:34:09 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static int	atoi3(const char *str, int *n, const int min)
{
	int	i;
	int	sg;

	while (isspace(*str))
		str++;
	sg = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	*n = 0;
	while (isdigit(*str))
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
	pthread_mutex_t	*fork;

	pdata->philo = malloc(pdata->number_of_philosophers * sizeof(pthread_t));
	pdata->fork = malloc(pdata->number_of_philosophers
			* sizeof(pthread_mutex_t));
	pdata->exit_status = (check_args || !pdata->philo || !pdata->fork);
	if (!pdata->exit_status)
	{
		fork = pdata->fork + pdata->number_of_philosophers;
		while (fork-- > pdata->fork && !pdata->exit_status)
			if (pthread_mutex_init(fork, NULL))
				destroy_forks(pdata, fork, 1);
	}
	return (pdata->exit_status);
}
