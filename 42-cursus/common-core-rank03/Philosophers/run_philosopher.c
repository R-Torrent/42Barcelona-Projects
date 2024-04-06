/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:26:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/06 12:39:57 by rtorrent         ###   ########.fr       */
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
	pthread_mutex_t *const	sl = philo->pdata->shared_locks;
	int						err[2];

	if (pthread_mutex_lock(sl + MASTER_LOCK)
		|| print_stamp(&philo->last_meal, t0, philo, "is eating")
		|| pthread_mutex_unlock(sl + MASTER_LOCK)
		|| usleep(philo->pdata->time_to_eat))
		return (1);
	*err = 0;
	if (!philo->meals_left--)
	{
		*err = pthread_mutex_lock(&philo->access);
		if (!*err)
		{
			philo->flags |= MEALS__OK;
			*err = pthread_mutex_unlock(&philo->access);
		}
	}
	if (*err || pthread_mutex_lock(sl + FORK_PICKING))
		return (1);
	err[LEFT] = pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	philo->fork[LEFT]->held = 0;
	err[RIGHT] = pthread_mutex_unlock(&philo->fork[RIGHT]->lock);
	philo->fork[RIGHT]->held = 0;
	return (pthread_mutex_unlock(sl + FORK_PICKING) || err[LEFT] || err[RIGHT]);
}

static int	pick_forks(t_philo *philo, struct timeval **t0)
{
	pthread_mutex_t *const	sl = philo->pdata->shared_locks;
	const int				f = philo->fork[LEFT] == philo->fork[RIGHT];
	int						err[2];

	if (pthread_mutex_lock(sl + FORK_PICKING))
		return (1);
	if (f || philo->fork[LEFT]->held || philo->fork[RIGHT]->held)
	{
		if (pthread_mutex_unlock(sl + FORK_PICKING) || usleep(FORK_RETRIAL))
			return (1);
		return (RETURN_FORK_RETRIAL);
	}
	err[LEFT] = (pthread_mutex_lock(sl + MASTER_LOCK)
			|| pthread_mutex_lock(&philo->fork[LEFT]->lock)
			|| print_stamp(NULL, t0, philo, "has taken a fork"));
	philo->fork[LEFT]->held = 1;
	philo->fork[RIGHT]->held = 1;
	err[RIGHT] = (pthread_mutex_lock(&philo->fork[RIGHT]->lock)
			|| print_stamp(NULL, t0, philo, "has taken a fork")
			|| pthread_mutex_unlock(sl + MASTER_LOCK));
	if (!pthread_mutex_unlock(sl + FORK_PICKING) && !err[LEFT] && !err[RIGHT])
		return (0);
	pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	pthread_mutex_unlock(&philo->fork[RIGHT]->lock);
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
	while (!ret || ret == RETURN_FORK_RETRIAL)
	{
		if (pthread_mutex_lock(&philo->access))
			break ;
		ret = philo->flags & TERMINATE;
		if (pthread_mutex_unlock(&philo->access))
			break ;
		if (ret)
			return (NULL);
		ret = pfunc[act](philo, (struct timeval *[]){philo->pdata->t0, NULL});
		if (ret != RETURN_FORK_RETRIAL)
			act = (act + 1) % NUMBER_OF_ACTIONS;
	}
	pthread_mutex_lock(&philo->access);
	philo->flags |= PHILO_ERR;
	pthread_mutex_unlock(&philo->access);
	return (NULL);
}
