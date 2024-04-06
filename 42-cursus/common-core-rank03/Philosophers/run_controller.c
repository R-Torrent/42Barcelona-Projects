/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:29:22 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/06 05:06:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	terminate_philos(t_philo *philo)
{
	t_philo *const	last = philo + philo->pdata->number_of_philos;

	while (philo < last)
	{
		if (pthread_mutex_lock(&philo->access))
			break ;
		philo->flags |= TERMINATE;
		if (pthread_mutex_unlock(&philo->access))
			break ;
		philo++;
	}
	return (philo == last);
}

static int	print_obituaries(t_data *pdata, int *flags)
{
	struct timeval	t1;
	unsigned int	elapsed;
	char			timestamp[12];
	t_philo			*philo;
	int				err;

	err = gettimeofday(&t1, NULL);
	if (!err)
		elapsed = tstamp(timestamp, (struct timeval *[]){pdata->t0, &t1});
	*flags = MEALS__OK;
	philo = pdata->philo;
	while (!err && philo < pdata->philo + pdata->number_of_philos)
	{
		err = pthread_mutex_lock(&philo->access);
		if (!(philo->flags & MEALS__OK))
			*flags &= ~MEALS__OK;
		if (elapsed - philo->last_meal >= pdata->time_to_die)
		{
			philo->flags |= TERMINATE;
			*flags |= TERMINATE;
			printf("%s %i died\n", timestamp, philo->n);
		}
		err = (err || pthread_mutex_unlock(&philo++->access));
	}
	return (err);
}

void	*run_controller(t_data *pdata)
{
	int	flags;
	int	err;

	err = 0;
	while (!err)
	{
		err = (pthread_mutex_lock(philo->pdata->shared_locks + MASTER_LOCK)
				|| print_obituaries(pdata, &flags));
		if (!err && flags)
		{
			err = terminate_philos(pdata->philo);
			break ;
		}
		err = (pthread_mutex_unlock(philo->pdata->shared_locks + MASTER_LOCK)
				|| err || usleep(DELAY_CONTROLLER_REPEAT));
	}
	pdata->contrl->exit = err;
	return (NULL);
}
