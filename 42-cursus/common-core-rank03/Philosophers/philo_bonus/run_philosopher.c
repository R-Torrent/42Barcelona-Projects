/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:11:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/17 20:05:24 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_sleep(t_philo *philo)
{
	print_stamp(NULL, philo, "is sleeping");
	wait_usec(philo->contrl, philo->contrl->pdata->time_to_sleep, 0);
}

static void	eat(t_philo *philo)
{
	t_data *const	pdata = philo->contrl->pdata;

	print_stamp(&philo->last_meal, philo, "is eating");
	wait_usec(philo->contrl, pdata->time_to_eat, 0);
	if (sem_post(pdata->shared_sems[FORKS])
		|| sem_post(pdata->shared_sems[FORKS]))
		philo->contrl->ret |= PHILO_ERR;
	if (!--philo->meals_left && sem_post(pdata->shared_sems[MLSOK]))
		philo->contrl->ret |= PHILO_ERR;
}

static void	pick_forks(t_philo *philo)
{
	t_data *const	pdata = philo->contrl->pdata;

	if (sem_wait(pdata->shared_sems[FORKS]))
		philo->contrl->ret |= PHILO_ERR;
	print_stamp(NULL, philo, "has taken a fork");
	if (sem_wait(pdata->shared_sems[FORKS]))
		philo->contrl->ret |= PHILO_ERR;
	print_stamp(NULL, philo, "has taken a fork");
}

static void	think(t_philo *philo)
{
	print_stamp(NULL, philo, "is thinking");
	wait_usec(philo->contrl, philo->contrl->pdata->time_to_think, 0);
}

void	run_philo(t_philo *philo)
{
	t_contrl *const		contrl = philo->contrl;
	const t_philo_func	pfunc[] = {think, pick_forks, eat, philo_sleep};
	enum e_philo_action	act;

	act = THINK;
	if (sem_wait(contrl->pdata->shared_sems[MASTR])
		|| sem_post(contrl->pdata->shared_sems[MASTR]))
		contrl->ret |= PHILO_ERR;
	while (!contrl->ret)
	{
		pfunc[act](philo);
		act = (act + 1) % NUMBER_OF_ACTIONS;
	}
}
