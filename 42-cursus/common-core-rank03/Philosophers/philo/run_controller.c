/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 02:29:22 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/22 02:31:58 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	place_digit(unsigned int n, char **pstr)
{
	long	x;

	x = n / 10L;
	if (x)
		place_digit(x, pstr);
	x = '0' + n % 10L;
	*(*pstr)++ = x;
}

int	tstamp(t_contrl *contrl, struct timeval *t, pthread_mutex_t *lock)
{
	char			*timestamp;
	unsigned int	diff_time;
	int				err;

	t[1] = t[2];
	err = (pthread_mutex_lock(lock) || gettimeofday(t + 2, NULL));
	contrl->elapsed = 1000 * (int)(t[2].tv_sec - t[0].tv_sec)
		+ ((int)t[2].tv_usec - (int)t[0].tv_usec) / 1000;
	timestamp = contrl->timestamp;
	place_digit(contrl->elapsed, &timestamp);
	*timestamp = '\0';
	err = (pthread_mutex_unlock(lock) || err);
	diff_time = 1000000 * (int)(t[2].tv_sec - t[1].tv_sec)
		+ ((int)t[2].tv_usec - (int)t[1].tv_usec);
	if (!err && diff_time < 1000)
		return (usleep(1000 - diff_time));
	return (err);
}

static int	print_obituaries(t_philo *philo, t_contrl *contrl,
	pthread_mutex_t *lock)
{
	t_philo *const	last = philo + philo->pdata->number_of_philos;
	int				err;

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
			err = (pthread_mutex_lock(lock) || err);
			printf("%s %i died\n", contrl->timestamp, philo->n);
			err = (pthread_mutex_unlock(lock) || err);
		}
		err = (pthread_mutex_unlock(&philo++->access) || err);
	}
	return (err);
}

void	*run_contrl(t_data *pdata)
{
	struct timeval	t[3];
	int				err;
	t_philo			*philo;

	err = (pthread_mutex_lock(pdata->shared_locks + MASTER_LOCK)
			|| pthread_mutex_unlock(pdata->shared_locks + MASTER_LOCK)
			|| gettimeofday(t, NULL));
	t[2] = t[0];
	while (!pdata->contrl->flags && !err)
	{
		err = print_obituaries(pdata->philo, pdata->contrl,
				pdata->shared_locks + PRINT_LOG);
		if (pdata->contrl->flags && !err)
		{
			philo = pdata->philo + pdata->number_of_philos;
			while (philo-- > pdata->philo)
			{
				err = pthread_mutex_lock(&philo->access);
				philo->flags |= TERMINATE;
				err = (pthread_mutex_unlock(&philo->access) || err);
			}
		}
		if (!err)
			err = tstamp(pdata->contrl, t, pdata->shared_locks + READ_TIME);
	}
	if (err)
		pdata->contrl->flags |= PHILO_ERR;
	return (NULL);
}
