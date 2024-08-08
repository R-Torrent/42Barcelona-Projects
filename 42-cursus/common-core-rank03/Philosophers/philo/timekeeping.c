/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timekeeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:53:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/08 19:38:59 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_stamp(unsigned int *dst, t_philo *philo, const char *str)
{
	t_data *const	pdata = philo->pdata;
	int				err;

	err = (pthread_mutex_lock(&philo->access)
			|| pthread_mutex_lock(pdata->shared_locks + PRINT_LOG)
			|| pthread_mutex_lock(pdata->shared_locks + READ_TIME));
	if (!err)
	{
		if (pdata->contrl->elapsed - philo->last_meal >= pdata->time_to_die)
			philo->flags |= TERMINATE;
		if (dst)
			*dst = pdata->contrl->elapsed;
		if (!(philo->flags & TERMINATE) && !pdata->contrl->first_death)
			printf("%s %i %s\n", pdata->contrl->timestamp, philo->n, str);
	}
	err = (pthread_mutex_unlock(pdata->shared_locks + READ_TIME) || err);
	err = (pthread_mutex_unlock(pdata->shared_locks + PRINT_LOG) || err);
	return (pthread_mutex_unlock(&philo->access) || err);
}

static void	place_digit(unsigned int n, char **pstr)
{
	const unsigned int	x = n / 10;

	if (x)
		place_digit(x, pstr);
	*(*pstr)++ = '0' + n % 10;
}

int	tstamp(t_contrl *contrl)
{
	unsigned int			prev_elapsed_ms;
	unsigned int			elapsed_ms;
	char					*timestamp;
	struct timeval *const	t = contrl->t;
	int						err;

	err = gettimeofday(t + 1, NULL);
	prev_elapsed_ms = contrl->elapsed / 1000;
	contrl->elapsed = 1000000 * (int)(t[1].tv_sec - t[0].tv_sec)
		+ ((int)t[1].tv_usec - (int)t[0].tv_usec);
	elapsed_ms = contrl->elapsed / 1000;
	if (prev_elapsed_ms != elapsed_ms)
	{
		timestamp = contrl->timestamp;
		place_digit(elapsed_ms, &timestamp);
		*timestamp = '\0';
	}
	return (err);
}

// this function runs a loop that executes usleep every 50 us until the
// desired intermission, 'lapse' in microseconds, is followed through
int	wait_usec(t_contrl *contrl, unsigned int lapse, t_philo *philo)
{
	unsigned int			reveille;
	pthread_mutex_t *const	time_lock = contrl->pdata->shared_locks + READ_TIME;
	int						err;

	err = pthread_mutex_lock(time_lock);
	reveille = contrl->elapsed + lapse;
	err = (pthread_mutex_unlock(time_lock) || err);
	while (!err)
	{
		if (philo)
		{
			err = pthread_mutex_lock(&philo->access);
			if (philo->flags & ~MEALS__OK)
				reveille = 0U;
			err = (pthread_mutex_unlock(&philo->access) || err);
		}
		err = (pthread_mutex_lock(time_lock) || err);
		if (!philo)
			err = (tstamp(contrl) || err);
		if (err || contrl->elapsed >= reveille)
			return (pthread_mutex_unlock(time_lock) || err);
		err = (pthread_mutex_unlock(time_lock) || usleep(50U));
	}
	return (err);
}
