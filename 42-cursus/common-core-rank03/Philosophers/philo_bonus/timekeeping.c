/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timekeeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:00:00 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/03 20:00:20 by rtorrent         ###   ########.fr       */
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
	long	x;

	x = n / 10L;
	if (x)
		place_digit(x, pstr);
	x = '0' + n % 10L;
	*(*pstr)++ = x;
}

int	tstamp(t_contrl *contrl)
{
	unsigned int			prev_elapsed;
	char					*timestamp;
	struct timeval *const	t = contrl->t;
	int						err;

	err = gettimeofday(t + 1, NULL);
	prev_elapsed = contrl->elapsed;
	contrl->elapsed = 1000000 * (int)(t[1].tv_sec - t[0].tv_sec)
		+ ((int)t[1].tv_usec - (int)t[0].tv_usec);
	if (prev_elapsed != contrl->elapsed)
	{
		timestamp = contrl->timestamp;
		place_digit(contrl->elapsed / 1000, &timestamp);
		*timestamp = '\0';
	}
	return (err);
}

// this function runs a loop that executes usleep every 100 us until the
// desired intermission, 'lapse' in microseconds, is followed through
int	wait_usec(t_contrl *contrl, unsigned int lapse, int is_contrl)
{
	unsigned int			reveille;
	pthread_mutex_t *const	time_lock = contrl->pdata->shared_locks + READ_TIME;
	int						err;

	err = pthread_mutex_lock(time_lock);
	reveille = contrl->elapsed + lapse;
	while (!err)
	{
		if (is_contrl)
			err = tstamp(contrl);
		lapse = contrl->elapsed;
		err = pthread_mutex_unlock(time_lock);
		if (err || lapse >= reveille)
			break ;
		usleep(100U);
		err = pthread_mutex_lock(time_lock);
	}
	return (err);
}
