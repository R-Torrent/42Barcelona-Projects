/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:26:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/21 02:17:45 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_sleep(t_philo *philo)
{
	return (print_stamp(NULL, philo, "is sleeping")
		|| wait_usec(philo->pdata->contrl, philo->pdata->time_to_sleep, philo));
}

static int	eat(t_philo *philo)
{
	int	err;

	if (print_stamp(&philo->last_meal, philo, "is eating")
		|| wait_usec(philo->pdata->contrl, philo->pdata->time_to_eat, philo))
		return (1);
	err = pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	err = (pthread_mutex_unlock(&philo->fork[RIGHT]->lock) || err);
	if (!err && !--philo->meals_left)
	{
		err = pthread_mutex_lock(&philo->access);
		if (!err)
		{
			philo->flags |= MEALS__OK;
			err = pthread_mutex_unlock(&philo->access);
		}
	}
	return (err);
}

// even-numbered philosophers pick the left fork first
// odd-numbered philosophers pick the right fork first
static int	pick_forks(t_philo *philo)
{
	const int	first = philo->n % 2;
	const int	second = first ^ 1;

	if (!(pthread_mutex_lock(&philo->fork[first]->lock)
			|| print_stamp(NULL, philo, "has taken a fork")
			|| pthread_mutex_lock(&philo->fork[second]->lock)
			|| print_stamp(NULL, philo, "has taken a fork")))
		return (0);
	pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	pthread_mutex_unlock(&philo->fork[RIGHT]->lock);
	return (1);
}

static int	think(t_philo *philo)
{
	return (print_stamp(NULL, philo, "is thinking")
		|| wait_usec(philo->pdata->contrl, philo->pdata->time_to_think, philo));
}

void	run_philo(t_philo *philo)
{
	const t_philo_func	pfunc[] = {think, pick_forks, eat, philo_sleep};
	enum e_philo_action	act;
	int					ret;

	act = THINK;
	ret = (pthread_detach(philo->thread)
			|| pthread_mutex_lock(philo->pdata->shared_locks + MASTER_LOCK)
			|| pthread_mutex_unlock(philo->pdata->shared_locks + MASTER_LOCK));
	while (!ret)
	{
		if (pthread_mutex_lock(&philo->access))
			break ;
		ret = philo->flags & TERMINATE;
		if (pthread_mutex_unlock(&philo->access))
			break ;
		if (ret)
			return ;
		ret = pfunc[act](philo);
		act = (act + 1) % NUMBER_OF_ACTIONS;
	}
	pthread_mutex_lock(&philo->access);
	philo->flags |= PHILO_ERR;
	pthread_mutex_unlock(&philo->access);
}
