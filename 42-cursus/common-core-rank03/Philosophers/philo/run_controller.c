/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:29:22 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/08 03:29:17 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_obituaries(t_philo *philo, int *flags)
{
	struct timeval	t1;
	unsigned int	elapsed;
	char			stamp[12];
	t_philo *const	last = philo + philo->pdata->number_of_philos;
	int				err;

	err = gettimeofday(&t1, NULL);
	if (!err)
		elapsed = tstamp(stamp, (struct timeval *[]){philo->pdata->t0, &t1});
	*flags = MEALS__OK;
	while (!err && philo < last)
	{
		err = pthread_mutex_lock(&philo->access);
		if (philo->flags & PHILO_ERR)
			*flags |= PHILO_ERR;
		if (!(philo->flags & MEALS__OK))
			*flags &= ~MEALS__OK;
		if (elapsed - philo->last_meal >= philo->pdata->time_to_die)
		{
			*flags |= TERMINATE;
			printf("%s %i died\n", stamp, philo->n);
		}
		err = (pthread_mutex_unlock(&philo++->access) || err);
	}
	return (err);
}

void	*run_contrl(t_data *pdata)
{
	int *const	flags = &pdata->contrl->flags;
	int			err;
	t_philo		*philo;

	while (!*flags && !err)
	{
		err = (pthread_mutex_lock(pdata->shared_locks + MASTER_LOCK)
				|| print_obituaries(pdata->philo, flags));
		if (*flags && !err)
		{
			philo = pdata->philo + pdata->number_of_philos;
			while (philo-- > pdata->philo)
			{
				err = pthread_mutex_lock(&philo->access);
				philo->flags |= TERMINATE;
				err = (pthread_mutex_unlock(&philo->access) || err);
			}
		}
		err = (pthread_mutex_unlock(pdata->shared_locks + MASTER_LOCK)
				|| err || usleep(DELAY_CONTROLLER_REPEAT));
	}
	if (err)
		*flags |= PHILO_ERR;
	return (NULL);
}
