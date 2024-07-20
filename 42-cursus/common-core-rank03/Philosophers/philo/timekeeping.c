/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timekeeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:53:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/20 19:50:54 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ft_strcpy(char *dest, char *src)
{
	char	*dst0;

	dst0 = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dst0);
}

int	print_stamp(unsigned int *dst, t_philo *philo, const char *str)
{
	char	timestamp[12];
	int		terminate;

	if (pthread_mutex_lock(&philo->access)
		|| pthread_mutex_lock(philo->pdata->shared_locks + READ_TIME))
		return (1);
	if (philo->pdata->contrl->elapsed - philo->last_meal
		>= philo->pdata->time_to_die)
		philo->flags |= TERMINATE;
	terminate = philo->flags & TERMINATE;
	if (!terminate)
	{
		if (dst)
			*dst = philo->pdata->contrl->elapsed;
		(void)ft_strcpy(timestamp, philo->pdata->contrl->timestamp);
	}
	if (pthread_mutex_unlock(philo->pdata->shared_locks + READ_TIME)
		|| pthread_mutex_unlock(&philo->access))
		return (1);
	if (terminate)
		return (0);
	if (pthread_mutex_lock(philo->pdata->shared_locks + PRINT_LOG))
		return (1);
	printf("%s %i %s\n", timestamp, philo->n, str);
	return (pthread_mutex_unlock(philo->pdata->shared_locks + PRINT_LOG));
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
int	wait_usec(t_contrl *contrl, unsigned int lapse, int id)
{
	unsigned int			reveille;
	pthread_mutex_t *const	time_lock = contrl->pdata->shared_locks + READ_TIME;
	int						err;

	err = pthread_mutex_lock(time_lock);
	reveille = contrl->elapsed + lapse;
	err = (pthread_mutex_unlock(time_lock) || err);
	while (!err && !(id && (contrl->pdata->philo + id - 1)->flags))
	{
		err = pthread_mutex_lock(time_lock);
		if (!id)
			err = (tstamp(contrl) || err);
		lapse = contrl->elapsed;
		err = (pthread_mutex_unlock(time_lock) || err);
		if (err || lapse >= reveille)
			break ;
		err = usleep(50U);
	}
	return (err);
}
