/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timekeeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:00:00 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/18 20:53:32 by rtorrent         ###   ########.fr       */
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

void	print_stamp(unsigned int *dst, t_philo *philo, const char *str)
{
	t_contrl *const	contrl = philo->contrl;
	char			timestamp[12];

	if (sem_wait(philo->access) || sem_wait(philo->read_time))
		contrl->ret |= PHILO_ERR;
	if (contrl->elapsed - philo->last_meal >= contrl->pdata->time_to_die)
		contrl->ret |= TERMINATE;
	if (!contrl->ret)
	{
		if (dst)
			*dst = contrl->elapsed;
		(void)ft_strcpy(timestamp, contrl->timestamp);
	}
	if (sem_post(philo->read_time) || sem_post(philo->access))
		contrl->ret |= PHILO_ERR;
	if (sem_wait(contrl->pdata->shared_sems[PRINT])
		|| !printf("%s %i %s\n", timestamp, philo->n, str)
		|| sem_post(contrl->pdata->shared_sems[PRINT]))
		contrl->ret |= PHILO_ERR;
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
		contrl->ret |= PHILO_ERR;
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
	unsigned int	reveille;

	if (sem_wait(read_time))
		contrl->ret |= PHILO_ERR;
	reveille = contrl->elapsed + lapse;
	if (sem_post(read_time))
		contrl->ret |= PHILO_ERR;
	while (!contrl->ret)
	{
		if (sem_wait(read_time))
			contrl->ret |= PHILO_ERR;
		if (is_contrl)
			tstamp(contrl);
		lapse = contrl->elapsed;
		if (sem_post(read_time))
			contrl->ret |= PHILO_ERR;
		if (contrl->ret || lapse >= reveille)
			break ;
		if (usleep(50U))
			contrl->ret |= PHILO_ERR;
	}
}
