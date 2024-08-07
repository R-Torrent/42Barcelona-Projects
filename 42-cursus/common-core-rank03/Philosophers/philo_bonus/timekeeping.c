/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timekeeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:00:00 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/07 20:28:12 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_stamp(unsigned int *dst, t_philo *philo, const char *str)
{
	t_contrl *const	contrl = philo->contrl;

	if (sem_wait(philo->access)
		|| sem_wait(contrl->pdata->shared_sems[PRINT])
		|| sem_wait(philo->read_time))
		contrl->err = 1;
	if (!contrl->err
		&& contrl->elapsed - philo->last_meal < contrl->pdata->time_to_die)
	{
		if (dst)
			*dst = contrl->elapsed;
		printf("%s %i %s\n", contrl->timestamp, philo->n, str);
	}
	if (sem_post(philo->read_time))
		contrl->err = 1;
	if (sem_post(contrl->pdata->shared_sems[PRINT]))
		contrl->err = 1;
	if (sem_post(philo->access))
		contrl->err = 1;
}

void	place_digit(unsigned int n, char **pstr)
{
	const unsigned int	x = n / 10;

	if (x)
		place_digit(x, pstr);
	*(*pstr)++ = '0' + n % 10;
}

void	tstamp(t_contrl *contrl)
{
	unsigned int			prev_elapsed_ms;
	unsigned int			elapsed_ms;
	char					*timestamp;
	struct timeval *const	t = contrl->t;

	if (gettimeofday(t + 1, NULL))
	{
		sem_wait(contrl->pdata->philo->access);
		contrl->err = 1;
		sem_post(contrl->pdata->philo->access);
	}
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
}

// this function runs a loop that executes usleep every 50 us until the
// desired intermission, 'lapse' in microseconds, is followed through
void	wait_usec(t_contrl *contrl, unsigned int lapse, int is_contrl)
{
	sem_t *const	read_time = contrl->pdata->philo->read_time;
	sem_t *const	access = contrl->pdata->philo->access;
	unsigned int	reveille;
	int				err;

	err = sem_wait(read_time);
	reveille = contrl->elapsed + lapse;
	err = (sem_post(read_time) || err);
	while (!err)
	{
		err = sem_wait(read_time);
		if (is_contrl)
			tstamp(contrl);
		lapse = contrl->elapsed;
		err = (sem_post(read_time) || sem_wait(access) || err);
		err = (contrl->err || err);
		err = (sem_post(access) || err);
		if (!err && lapse >= reveille)
			return ;
		err = (usleep(50U) || err);
	}
	sem_wait(access);
	contrl->err = 1;
	sem_post(access);
}
