/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:26:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/01 02:27:23 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	drop_forks(pthread_mutex_t *forks_locked, t_philo *philo)
{
	int	err[2];

	philo->meals_left--;
	if (pthread_mutex_lock(forks_locked))
		return (1);
	err[LEFT] = pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	philo->fork[LEFT]->held = 0;
	err[RIGHT] = pthread_mutex_unlock(&philo->fork[RIGHT]->lock);
	philo->fork[RIGHT]->held = 0;
	return (pthread_mutex_unlock(forks_locked) || err[LEFT] || err[RIGHT]);
}

static int	pick_forks(const struct timeval *t0, pthread_mutex_t *forks_locked,
		t_philo *philo, const char *str)
{
	const int	f = philo->fork[LEFT] != philo->fork[RIGHT];
	int			err[4];

	while (1)
	{
		*err = pthread_mutex_lock(forks_locked);
		if (!*err && f && !philo->fork[LEFT]->held && !philo->fork[RIGHT]->held)
			break ;
		if (*err || pthread_mutex_unlock(forks_locked) || usleep(DELAY_FORK_RE))
			return (1);
	}
	err[LEFT] = pthread_mutex_lock(&philo->fork[LEFT]->lock);
	err[2] = print_stamp(NULL, t0, philo->n, str);
	philo->fork[LEFT]->held = 1;
	err[RIGHT] = pthread_mutex_lock(&philo->fork[RIGHT]->lock);
	err[3] = print_stamp(NULL, t0, philo->n, str);
	philo->fork[RIGHT]->held = 1;
	if (!err[LEFT] && !err[RIGHT] && !err[2] && !err[3])
		return (0);
	if (!err[LEFT])
		pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	if (!err[RIGHT])
		pthread_mutex_unlock(&philo->fork[RIGHT]->lock);
	return (1);
}

void	*run_philo(struct s_args *philo_args)
{
	t_data *const	pdata = philo_args->pdata;
	t_philo *const	philo = pdata->philo + philo_args->n - 1;
	const char		*str[] = {"is thinking", "has taken a fork", "is eating",
		"", "is sleeping"};

	while (!(print_stamp(NULL, pdata->t0, philo->n, str[THINKING])
			|| pick_forks(pdata->t0, &pdata->shared_locks[FORK_PICKING],
				philo, str[PICKING])
			|| print_stamp(&philo->last_meal, pdata->t0, philo->n, str[EATING])
			|| usleep(pdata->time_to_eat)
			|| drop_forks(&pdata->shared_locks[FORK_PICKING], philo)
			|| print_stamp(NULL, pdata->t0, philo->n, str[SLEEPING])
			|| usleep(pdata->time_to_sleep)))
		;
	return (NULL);
}
