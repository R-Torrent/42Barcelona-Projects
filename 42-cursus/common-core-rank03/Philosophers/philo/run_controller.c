/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:29:22 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/05 16:42:16 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_obituaries(t_philo *philo, t_contrl *contrl)
{
	t_philo *const			last = philo + philo->pdata->number_of_philos;
	pthread_mutex_t *const	print_lock = philo->pdata->shared_locks + PRINT_LOG;
	int						err;

	contrl->flags = MEALS__OK;
	err = 0;
	while (!err && philo < last)
	{
		err = pthread_mutex_lock(&philo->access);
		if (philo->flags & PHILO_ERR)
			contrl->flags |= PHILO_ERR;
		if (!(philo->flags & MEALS__OK))
			contrl->flags &= ~MEALS__OK;
		if (contrl->elapsed - philo->last_meal >= philo->pdata->time_to_die)
		{
			contrl->flags |= TERMINATE;
			err = (pthread_mutex_lock(print_lock) || err);
			printf("%s %i died\n", contrl->timestamp, philo->n);
			err = (pthread_mutex_unlock(print_lock) || err);
		}
		err = (pthread_mutex_unlock(&philo++->access) || err);
	}
	return (err);
}

// main loop runs once every millisecond
void	*run_contrl(t_data *pdata)
{
	struct timeval	t[2];
	t_contrl *const	contrl = pdata->contrl;
	t_philo			*philo;
	int				err;

	contrl->t = t;
	err = (pthread_mutex_lock(pdata->shared_locks + MASTER_LOCK)
			|| pthread_mutex_unlock(pdata->shared_locks + MASTER_LOCK)
			|| gettimeofday(t, NULL));
	while (!err && !contrl->flags)
		err = (print_obituaries(pdata->philo, contrl)
				|| wait_usec(contrl, 1000
					- (t[1].tv_usec % 1000 - t[0].tv_usec % 1000), 1) || err);
	philo = pdata->philo;
	while (philo < pdata->philo + pdata->number_of_philos)
	{
		err = (pthread_mutex_lock(&philo->access) || err);
		philo->flags |= TERMINATE;
		err = (pthread_mutex_unlock(&philo++->access) || err);
	}
	if (err)
		contrl->flags |= PHILO_ERR;
	return (NULL);
}
