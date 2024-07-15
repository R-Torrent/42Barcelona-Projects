/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:51 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/15 14:08:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	print_obituary(t_contrl *contrl, t_philo *philo)
{
	t_data *const	pdata = contrl->pdata;

	if (contrl->elapsed - philo->last_meal >= pdata->time_to_die)
	{
		sem_wait(pdata->shared_sems[PRINT]);
		printf("%s %i died\n", contrl->timestamp, philo->n);
		sem_post(pdata->shared_sems[PRINT]);
		return (1);
	}
	return (0);
}

// main loop runs once every millisecond
static void	run_contrl(t_contrl *contrl)
{
	struct timeval	t[2];
	t_data *const	pdata = contrl->pdata;

	contrl->t = t;
	contrl->ret = (contrl->ret || sem_wait(pdata->shared_sems[MASTR])
			|| sem_post(pdata->shared_sems[MASTR]) || gettimeofday(t, NULL));
	while (!contrl->ret)
		contrl->ret = (print_obituary(contrl, pdata->philo)
				|| tstamp(contrl)
				|| wait_usec(contrl, 1000 - contrl->elapsed % 1000, 1)
				|| contrl->ret);
	sem_post(pdata->shared_sems[TERMN]);
}

void	run_philo(t_philo *philo)
{
	t_contrl *const	contrl = philo->contrl;
	t_data *const	pdata = contrl->pdata;
	char			sname[2][20];

	if (!philo->meals_left)
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
	loop_philo(philo);
	sem_post(pdata->shared_sems[TERMN]);
	if (philo->access != SEM_FAILED)
		sem_close(philo->access);
	if (philo->read_time != SEM_FAILED)
		sem_close(philo->read_time);
	pthread_join(contrl->thread_controller, NULL);
	pthread_join(contrl->thread_cleaner, NULL);
}
