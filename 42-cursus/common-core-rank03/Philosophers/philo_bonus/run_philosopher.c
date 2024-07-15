/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:11:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/15 02:26:53 by rtorrent         ###   ########.fr       */
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
	err = (sem_post(pdata->shared_sems[FORKS])
			|| sem_post(pdata->shared_sems[FORKS]));
	if (!err && !--philo->meals_left)
		err = sem_post(pdata->shared_sems[MLSOK]);
	return (err);
}

static int	pick_forks(t_philo *philo)
{
	t_data *const	pdata = philo->contrl->pdata;

	return (sem_wait(pdata->shared_sems[FORKS])
		|| print_stamp(NULL, philo, "has taken a fork")
		|| sem_wait(pdata->shared_sems[FORKS])
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
	t_data *const		pdata = contrl->pdata;
	char				sname[2][20];
	const t_philo_func	pfunc[] = {think, pick_forks, eat, philo_sleep};
	enum e_philo_action	act;

	act = THINK;
	if (!pdata->philo->meals_left)
		sem_post(pdata->shared_sems[MLSOK]);
	philo->access = sem_open(sem_name(sname[0], philo->n, "ACCESS"),
			S_OFLAG, S_MODE, 1);
	philo->read_time = sem_open(sem_name(sname[1], philo->n, "RDTIME"),
			S_OFLAG, S_MODE, 1);
	contrl->ret = (philo->access == SEM_FAILED || sem_unlink(sname[0]));
	contrl->ret = (philo->read_time == SEM_FAILED || sem_unlink(sname[1])
			|| contrl->ret);
	contrl->ret = (contrl->ret || pthread_create(&contrl->thread_controller,
				NULL, (void *)run_contrl, contrl)
			|| pthread_create(&contrl->thread_cleaner, NULL,
				(void *)run_cleaner, pdata)
			|| sem_wait(pdata->shared_sems[MASTR])
			|| sem_post(pdata->shared_sems[MASTR]));
	while (!contrl->ret)
	{
		contrl->ret = pfunc[act](philo);
		act = (act + 1) % NUMBER_OF_ACTIONS;
	}
	sem_post(pdata->shared_sems[TERMN]);
	if (philo->access != SEM_FAILED)
		sem_close(philo->access);
	if (philo->read_time != SEM_FAILED)
		sem_close(philo->read_time);
	pthread_join(contrl->thread_controller, NULL);
	pthread_join(contrl->thread_cleaner, NULL);
}
