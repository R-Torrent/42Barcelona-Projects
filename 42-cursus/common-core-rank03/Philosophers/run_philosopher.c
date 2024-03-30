/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:26:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/30 15:39:25 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
static int	eat(t_data *pdata
	if (usleep((unsigned int)pdata->time_to_eat)
		|| pthread_mutex_unlock(&fork[LEFT]) || pthread_mutex_unlock(&fork[RIGHT]))
		return (1);
	*fork_held[LEFT] = 0;
	*fork_held[RIGHT] = 0;
	return (0);
}
*/
int	pick_forks(t_data *const pdata, const int nphilo, const int *nforks,
		char *timestamp)
{
	const int				*fork_held[2] = {pdata->fork_held + nforks[LEFT],
		pdata->fork_held = nforks[RIGHT]};
	const pthread_mutex_t	*fork[2] = {pdata->fork_held + nforks[LEFT],
		pdata->fork + nforks[RIGHT]};
	struct timeval			tfork[2];
	int						hand;

	while (true)
	{
		if (pthread_mutex_lock(pdata->forks_locked))
			return (1);
		if (!fork_held[LEFT] && nphilo != 1 && !fork_held[RIGHT])
			break ;
		if (pthread_mutex_unlock(pdata->forks_locked) || usleep(DELAY_FORK_RE))
			return (1);
	}
	hand = LEFT;
	while (hand <= RIGHT && !gettimeofday(&tfork[hand])
		&& !pthread_mutex_lock(fork[hand]))
	{
		*fork_held[hand] = 1;
		printf("%s %i has taken a fork\n", tstamp(timestamp, pdata->t0,
				&tfork[hand++]), nphilo);
	}
	return (hand <= RIGHT);
}

int	think(t_data *const pdata, const int nphilo, char *timestamp)
{
	struct timeval	tthink;
	const int		error_status = gettimeofday(&tthink);
	
	if (!error_status)
		printf("%s %i has taken a fork\n", tstamp(timestamp, pdata->t0, &tthink), nphilo);
	return (error_status);
}
