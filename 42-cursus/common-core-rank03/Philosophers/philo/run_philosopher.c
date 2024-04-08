/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:26:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/08 04:05:58 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_sleep(t_philo *philo, struct timeval **t0)
{
	pthread_mutex_t *const	mlock = philo->pdata->shared_locks + MASTER_LOCK;

	return (pthread_mutex_lock(mlock)
		|| print_stamp(NULL, t0, philo, "is sleeping")
		|| pthread_mutex_unlock(mlock)
		|| usleep(philo->pdata->time_to_sleep));
}

static int	eat(t_philo *philo, struct timeval **t0)
{
	int	err;

	if (pthread_mutex_lock(philo->pdata->shared_locks + MASTER_LOCK)
		|| print_stamp(&philo->last_meal, t0, philo, "is eating")
		|| pthread_mutex_unlock(philo->pdata->shared_locks + MASTER_LOCK)
		|| usleep(philo->pdata->time_to_eat))
		return (1);
	err = 0;
	if (!--philo->meals_left)
	{
		err = pthread_mutex_lock(&philo->access);
		if (!err)
		{
			philo->flags |= MEALS__OK;
			err = pthread_mutex_unlock(&philo->access);
		}
	}
	err = (pthread_mutex_unlock(&philo->fork[LEFT]->lock) || err);
	err = (pthread_mutex_unlock(&philo->fork[RIGHT]->lock) || err);
	return (err);
}

// even-numbered philosophers pick the left fork first
// odd-numbered philosophers pick the right fork first
static int	pick_forks(t_philo *philo, struct timeval **t0)
{
	const int	first = philo->n % 2;
	const int	second = first ^ 1;

	if (!(pthread_mutex_lock(&philo->fork[first]->lock)
			|| pthread_mutex_lock(philo->pdata->shared_locks + MASTER_LOCK)
			|| print_stamp(NULL, t0, philo, "has taken a fork")
			|| pthread_mutex_unlock(philo->pdata->shared_locks + MASTER_LOCK)
			|| pthread_mutex_lock(&philo->fork[second]->lock)
			|| pthread_mutex_lock(philo->pdata->shared_locks + MASTER_LOCK)
			|| print_stamp(NULL, t0, philo, "has taken a fork")
			|| pthread_mutex_unlock(philo->pdata->shared_locks + MASTER_LOCK)))
		return (0);
	pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	pthread_mutex_unlock(&philo->fork[RIGHT]->lock);
	pthread_mutex_unlock(philo->pdata->shared_locks + MASTER_LOCK);
	return (1);
}

static int	think(t_philo *philo, struct timeval **t0)
{
	pthread_mutex_t *const	mlock = philo->pdata->shared_locks + MASTER_LOCK;

	return (pthread_mutex_lock(mlock)
		|| print_stamp(NULL, t0, philo, "is thinking")
		|| pthread_mutex_unlock(mlock));
}

void	*run_philo(t_philo *philo)
{
	const t_philo_func	pfunc[] = {think, pick_forks, eat, philo_sleep};
	enum e_philo_action	act;
	int					ret;

	act = THINK;
	ret = (pthread_mutex_lock(philo->pdata->shared_locks + MASTER_LOCK)
			|| pthread_mutex_unlock(philo->pdata->shared_locks + MASTER_LOCK));
	while (!ret)
	{
		if (pthread_mutex_lock(&philo->access))
			break ;
		ret = philo->flags & TERMINATE;
		if (pthread_mutex_unlock(&philo->access))
			break ;
		if (ret)
			return (NULL);
		ret = pfunc[act](philo, (struct timeval *[]){philo->pdata->t0, NULL});
		act = (act + 1) % NUMBER_OF_ACTIONS;
	}
	pthread_mutex_lock(&philo->access);
	philo->flags |= PHILO_ERR;
	pthread_mutex_unlock(&philo->access);
	return (NULL);
}
