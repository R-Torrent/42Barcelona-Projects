/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:11:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/07 20:27:45 by rtorrent         ###   ########.fr       */
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
	int				err;

	print_stamp(&philo->last_meal, philo, "is eating");
	wait_usec(philo->contrl, pdata->time_to_eat, 0);
	err = (sem_post(pdata->shared_sems[FORKS])
			|| sem_post(pdata->shared_sems[FORKS]));
	if (!--philo->meals_left && sem_post(pdata->shared_sems[MLSOK]) && !err)
		err = 1;
	if (err)
	{
		sem_wait(philo->access);
		philo->contrl->err = 1;
		sem_post(philo->access);
	}
}

static void	pick_forks(t_philo *philo)
{
	t_data *const	pdata = philo->contrl->pdata;
	int				err;

	err = sem_wait(pdata->shared_sems[FORKS]);
	print_stamp(NULL, philo, "has taken a fork");
	if (sem_wait(pdata->shared_sems[FORKS]) && !err)
		err = 1;
	print_stamp(NULL, philo, "has taken a fork");
	if (err)
	{
		sem_wait(philo->access);
		philo->contrl->err = 1;
		sem_post(philo->access);
	}
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

	act = THINK;
	while (!(sem_wait(philo->access)
			|| philo->contrl->err
			|| sem_post(philo->access)))
	{
		pfunc[act](philo);
		act = (act + 1) % NUMBER_OF_ACTIONS;
	}
}
