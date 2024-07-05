/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:51 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/04 23:13:55 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_obituary(t_philo *philo, t_contrl *contrl)
{
	t_philo *const			last = philo + philo->pdata->number_of_philos;
	pthread_mutex_t *const	print_lock = philo->pdata->shared_locks + PRINT_LOG;
	int						err;

	if (contrl->elapsed - philo->last_meal >= philo->pdata->time_to_die)
	{
		contrl->flags |= TERMINATE;
		err = (pthread_mutex_lock(print_lock) || err);
		printf("%s %i died\n", contrl->timestamp, philo->n);
		err = (pthread_mutex_unlock(print_lock) || err);
		}
		err = (pthread_mutex_unlock(&philo++->access) || err);
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
		ret = (print_obituaries(pdata->philo, contrl)
				|| tstamp(contrl) || wait_usec(contrl, 1000
					- (t[1].tv_usec % 1000 - t[0].tv_usec % 1000), 1) || err);
	sem_post(pdata->sem[TERMN]);
	return (NULL);
}
