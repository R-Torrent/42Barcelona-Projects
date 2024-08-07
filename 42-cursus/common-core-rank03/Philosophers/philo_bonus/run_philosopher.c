/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:11:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/07 13:23:02 by rtorrent         ###   ########.fr       */
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
	t_data *const		pdata = philo->contrl->pdata;
	static unsigned int	not_first_thoughts;

	print_stamp(NULL, philo, "is thinking");
	if (not_first_thoughts++ || philo->n
		> (pdata->number_of_philos / 2 + pdata->number_of_philos % 2))
		wait_usec(philo->contrl, pdata->time_to_think, 0);
}

void	run_philo(t_philo *philo)
{
	const t_philo_func	pfunc[] = {think, pick_forks, eat, philo_sleep};
	enum e_philo_action	act;
	int					ret;

	act = THINK;
	ret = (sem_wait(philo->contrl->pdata->shared_sems[MASTR])
			|| sem_post(philo->contrl->pdata->shared_sems[MASTR]));
	while (!ret)
	{
		if (sem_wait(philo->access))
			break ;
		ret = (philo->contrl->ret & TERMINATE);
		if (sem_post(philo->access))
			break ;
		if (ret)
			return ;
		pfunc[act](philo);
		act = (act + 1) % NUMBER_OF_ACTIONS;
		sem_wait(philo->access);
		ret = philo->contrl->ret & PHILO_ERR;
		sem_post(philo->access);
	}
	sem_wait(philo->access);
	philo->contrl->ret |= PHILO_ERR;
	sem_post(philo->access);
}
