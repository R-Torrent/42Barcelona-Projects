/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:51 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/05 16:04:38 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	}
	return (err);
}

// main loop runs once every millisecond
void	*run_contrl(t_contrl *contrl)
{
	struct timeval	t[2];
	t_data *const	pdata = contrl->pdata;
	int				ret;

	contrl->t = t;
	ret = (sem_wait(pdata->sem[MASTR])
			|| sem_post(pdata->sem[MASTR])
			|| gettimeofday(t, NULL));
	while (!ret)
		ret = (print_obituary(contrl, pdata->philo)
				|| tstamp(contrl) || wait_usec(contrl, 1000
					- (t[1].tv_usec % 1000 - t[0].tv_usec % 1000), 1));
	sem_post(pdata->sem[TERMN]);
	return (NULL);
}
