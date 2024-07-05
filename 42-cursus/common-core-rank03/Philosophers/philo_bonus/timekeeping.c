/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timekeeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:00:00 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/05 16:05:43 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_stamp(unsigned int *dst, t_philo *philo, const char *str)
{
	t_contrl *const	contrl = philo->contrl;
	char			timestamp[12];

	if (philo->contrl->elapsed - philo->last_meal
		>= philo->contrl->pdata->time_to_die)
		return (1);
	if (dst)
		*dst = philo->contrl->elapsed;
	if (sem_wait(contrl->pdata->sem[PRINT]))
		return (1);
	printf("%s %i %s\n", timestamp, philo->n, str);
	return (sem_post(contrl->pdata->sem[PRINT]));
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
	unsigned int	reveille;
	int				err;

	reveille = contrl->elapsed + lapse;
	err = 0;
	while (!err)
	{
		if (is_contrl)
			err = tstamp(contrl);
		if (err || contrl->elapsed >= reveille)
			break ;
		usleep(100U);
	}
	return (err);
}
