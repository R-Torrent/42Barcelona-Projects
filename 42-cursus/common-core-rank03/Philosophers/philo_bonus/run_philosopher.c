/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:11:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/09 00:36:48 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	philo_sleep(t_philo *philo)
{
	return (print_stamp(NULL, philo, "is sleeping")
		|| wait_usec(philo->contrl, philo->contrl->pdata->time_to_sleep, 0));
}

static int	eat(t_philo *philo)
{
	t_data *const	pdata = philo->contrl->pdata;
	int				err;

	if (print_stamp(&philo->last_meal, philo, "is eating")
		|| wait_usec(philo->contrl, pdata->time_to_eat, 0))
		return (1);
	err = (sem_post(pdata->sem[FORKS]) || sem_post(pdata->sem[FORKS]));
	if (!err && !--philo->meals_left)
		err = sem_post(pdata->sem[MLSOK]);
	return (err);
}

static int	pick_forks(t_philo *philo)
{
	t_data *const	pdata = philo->contrl->pdata;

	return (sem_wait(pdata->sem[FORKS])
		|| print_stamp(NULL, philo, "has taken a fork")
		|| sem_wait(pdata->sem[FORKS])
		|| print_stamp(NULL, philo, "has taken a fork"));
}

static int	think(t_philo *philo)
{
	return (print_stamp(NULL, philo, "is thinking")
		|| wait_usec(philo->contrl, philo->contrl->pdata->time_to_think, 0));
}

void	run_philo(t_philo *philo)
{
	t_contrl *const		contrl = philo->contrl;
	const t_philo_func	pfunc[] = {think, pick_forks, eat, philo_sleep};
	enum e_philo_action	act;

	act = THINK;
	contrl->ret = (contrl->ret || pthread_create(&contrl->thread_controller,
				NULL, (void *(*)(void *))run_contrl, contrl)
			|| pthread_create(&contrl->thread_cleaner, NULL,
				(void *(*)(void *))run_cleaner, contrl->pdata)
			|| pthread_detach(contrl->thread_controller)
			|| sem_wait(contrl->pdata->sem[MASTR])
			|| sem_post(contrl->pdata->sem[MASTR]));
	while (!contrl->ret)
	{
		contrl->ret = pfunc[act](philo);
		act = (act + 1) % NUMBER_OF_ACTIONS;
	}
	sem_post(contrl->pdata->sem[TERMN]);
	pthread_join(contrl->thread_cleaner, NULL);
	exit(0);
}
