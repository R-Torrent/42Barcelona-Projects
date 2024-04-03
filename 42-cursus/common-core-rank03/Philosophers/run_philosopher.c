/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:26:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/03 02:19:44 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_sleep(t_philo *philo, const struct timeval *t0,
	const char *str)
{
	t_data *const	pdata = philo->pdata;

	return (print_stamp(NULL, t0, philo, str) || usleep(pdata->time_to_sleep));
}

static int	eat(t_philo *philo, const struct timeval *t0, const char *str)
{
	t_data *const	pdata = philo->pdata;
	int				err[2];

	if (print_stamp(&philo->last_meal, t0, philo, str)
		|| usleep(pdata->time_to_eat))
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
	if (*err || pthread_mutex_lock(pdata->shared_locks + FORK_PICKING))
		return (1);
	err[LEFT] = pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	philo->fork[LEFT]->held = 0;
	err[RIGHT] = pthread_mutex_unlock(&philo->fork[RIGHT]->lock);
	philo->fork[RIGHT]->held = 0;
	return (pthread_mutex_unlock(pdata->shared_locks + FORK_PICKING)
		|| err[LEFT] || err[RIGHT]);
}

static int	pick_forks(t_philo *philo, const struct timeval *t0,
	const char *str)
{
	t_data *const	pdata = philo->pdata;
	const int		f = philo->fork[LEFT] == philo->fork[RIGHT];
	int				err[4];

	*err = pthread_mutex_lock(pdata->shared_locks + FORK_PICKING);
	if (!*err && (f || philo->fork[LEFT]->held || philo->fork[RIGHT]->held))
	{
		*err = pthread_mutex_unlock(pdata->shared_locks + FORK_PICKING);
		if (*err || usleep(DELAY_FORK_RETRIAL))
			return (1);
		return (RETURN_FORK_RETRIAL);
	}
	err[LEFT] = pthread_mutex_lock(&philo->fork[LEFT]->lock);
	err[2] = print_stamp(NULL, t0, philo, str);
	philo->fork[LEFT]->held = 1;
	err[RIGHT] = pthread_mutex_lock(&philo->fork[RIGHT]->lock);
	err[3] = print_stamp(NULL, t0, philo, str);
	philo->fork[RIGHT]->held = 1;
	if (!err[LEFT] && !err[RIGHT] && !err[2] && !err[3])
		return (0);
	if (!err[LEFT])
		pthread_mutex_unlock(&philo->fork[LEFT]->lock);
	if (!err[RIGHT])
		pthread_mutex_unlock(&philo->fork[RIGHT]->lock);
	return (1);
}

static int	think(t_philo *philo, const struct timeval *t0, const char *str)
{
	return (print_stamp(NULL, t0, philo, str));
}

void	*run_philo(t_philo *philo)
{
	t_data *const		pdata = philo->pdata;
	const char			*str[] = {"is thinking", "has taken a fork",
		"is eating", "is sleeping"};
	const t_philo_func	philo_func[] = {think, pick_forks, eat, philo_sleep};
	enum e_philo_action	action;
	int					ret;

	if (!pthread_mutex_lock(pdata->shared_locks + INIT_SIM)
		&& !pthread_mutex_unlock(pdata->shared_locks + INIT_SIM))
	{
		action = THINK;
		while (1)
		{
			ret = philo_func[action](philo, philo->pdata->t0, str[action]);
			if (ret == RETURN_FORK_RETRIAL)
				continue ;
			else if (ret)
				break ;
			action = (action + 1) % NUMBER_OF_ACTIONS;
		}
	}
	pthread_mutex_lock(&philo->access);
	philo->flags |= PHILO_ERR;
	pthread_mutex_unlock(&philo->access);
	return (NULL);
}
