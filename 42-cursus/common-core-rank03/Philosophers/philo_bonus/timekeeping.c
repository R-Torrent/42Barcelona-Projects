/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timekeeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:00:00 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/17 14:02:02 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	t_contrl *const	contrl = philo->contrl;
	char			timestamp[12];
	int				ret;

	ret = (sem_wait(philo->access) || sem_wait(philo->read_time)
			|| contrl->elapsed - philo->last_meal
			>= contrl->pdata->time_to_die);
	if (!ret)
	{
		if (dst)
			*dst = contrl->elapsed;
		(void)ft_strcpy(timestamp, contrl->timestamp);
	}
	ret = (sem_post(philo->read_time) || sem_post(philo->access) || ret);
	if (!ret)
		ret = sem_wait(contrl->pdata->shared_sems[PRINT]);
	if (!ret)
		printf("%s %i %s\n", timestamp, philo->n, str);
	if (!ret)
		ret = sem_post(contrl->pdata->shared_sems[PRINT]);
	return (ret);
}

void	place_digit(unsigned int n, char **pstr)
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
int	wait_usec(t_contrl *contrl, unsigned int lapse, int is_contrl)
{
	sem_t *const	read_time = contrl->pdata->philo->read_time;
	unsigned int	reveille;
	int				err;

	err = sem_wait(read_time);
	reveille = contrl->elapsed + lapse;
	while (!err)
	{
		if (is_contrl)
			err = tstamp(contrl);
		lapse = contrl->elapsed;
		err = (sem_post(read_time) || err);
		if (err || lapse >= reveille)
			break ;
		usleep(50U);
		err = sem_wait(read_time);
	}
	return (err);
}
