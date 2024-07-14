/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:51 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/14 14:51:48 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	print_obituary(t_contrl *contrl, t_philo *philo)
{
	t_data *const	pdata = contrl->pdata;
	int				err;

	err = 0;
	if (contrl->elapsed - philo->last_meal >= pdata->time_to_die)
	{
		err = sem_wait(pdata->sem[PRINT]);
		printf("%s %i died\n", contrl->timestamp, philo->n);
		err = (sem_post(pdata->sem[PRINT]) || err);
		contrl->ret = 1;
	}
	return (err);
}

// main loop runs once every millisecond
void	run_contrl(t_contrl *contrl)
{
	struct timeval	t[2];
	t_data *const	pdata = contrl->pdata;

	contrl->t = t;
	contrl->ret = (contrl->ret || sem_wait(pdata->sem[MASTR])
			|| sem_post(pdata->sem[MASTR]) || gettimeofday(t, NULL));
	while (!contrl->ret)
		contrl->ret = (print_obituary(contrl, pdata->philo)
				|| tstamp(contrl) || wait_usec(contrl, 1000 - contrl->elapsed % 1000, 1)
				|| contrl->ret);
	sem_post(pdata->sem[TERMN]);
}
