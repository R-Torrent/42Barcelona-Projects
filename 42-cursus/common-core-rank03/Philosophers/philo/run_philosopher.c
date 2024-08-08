/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:26:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/08 20:49:06 by rtorrent         ###   ########.fr       */
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
	if (philo->fork[LEFT]->n == philo->fork[RIGHT]->n)
		return (err);
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

// even-numbered philosophers pick the left (= same-numbered) fork first
// odd-numbered philosophers pick the right (= succesor) fork next
static int	pick_forks(t_philo *philo)
{
	const int	first = philo->n % 2;
	const int	second = first ^ 1;
	int			err;

	err = 0;
	if (pthread_mutex_lock(&philo->fork[first]->lock)
		|| print_stamp(NULL, philo, "has taken a fork"))
		err = (pthread_mutex_unlock(&philo->fork[first]->lock) || 1);
	else if (philo->fork[first]->n == philo->fork[second]->n)
	{
		err = pthread_mutex_lock(&philo->access);
		philo->flags |= TERMINATE;
		err = (pthread_mutex_unlock(&philo->access) || err);
	}
	else if (pthread_mutex_lock(&philo->fork[second]->lock)
		|| print_stamp(NULL, philo, "has taken a fork"))
		err = (pthread_mutex_unlock(&philo->fork[second]->lock) || 1);
	return (err);
}

static int	think(t_philo *philo)
{
	t_data *const	pdata = philo->pdata;
	int				ret;

	ret = print_stamp(NULL, philo, "is thinking");
	if (!ret && philo->not_first_thoughts++)
		ret = wait_usec(pdata->contrl, pdata->time_to_think, philo);
	return (ret);
}

void	run_philo(t_philo *philo)
{
	const t_philo_func	pfunc[] = {think, pick_forks, eat, philo_sleep};
	enum e_philo_action	act;
	int					ret;

	act = THINK;
	ret = 0;
	while (!ret)
	{
		if (pthread_mutex_lock(&philo->access))
			break ;
		ret = (philo->flags & TERMINATE && act != EAT);
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
