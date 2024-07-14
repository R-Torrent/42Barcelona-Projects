/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:51 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/14 20:28:08 by rtorrent         ###   ########.fr       */
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
void	run_contrl(t_contrl *contrl)
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
