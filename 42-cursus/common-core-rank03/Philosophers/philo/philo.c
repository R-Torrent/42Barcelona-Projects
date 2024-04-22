/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:26:30 by rtorrent          #+#    #+#             */
/*   Updated: 2024/04/22 01:45:42 by rtorrent         ###   ########.fr       */
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

	if (pthread_mutex_lock(&philo->access)
		|| pthread_mutex_lock(philo->pdata->shared_locks + READ_TIME))
		return (1);
	if (philo->pdata->contrl->elapsed - philo->last_meal
		>= philo->pdata->time_to_die)
		philo->flags |= TERMINATE;
	if (!(philo->flags & TERMINATE))
	{
		if (dst)
			*dst = philo->pdata->contrl->elapsed;
		(void)ft_strcpy(timestamp, philo->pdata->contrl->timestamp);
	}
	if (pthread_mutex_unlock(philo->pdata->shared_locks + READ_TIME)
		|| pthread_mutex_unlock(&philo->access))
		return (1);
	if (!(philo->flags & TERMINATE))
	{
		if (pthread_mutex_lock(philo->pdata->shared_locks + PRINT_LOG))
			return (1);
		printf("%s %i %s\n", timestamp, philo->n, str);
		return (pthread_mutex_unlock(philo->pdata->shared_locks + PRINT_LOG));
	}
	return (0);
}

void	destroy_locks(t_data *pdata, t_fork *fork, int error)
{
	t_fork *const	lastf = pdata->fork + pdata->number_of_philos;
	t_philo *const	lastp = pdata->philo + pdata->number_of_philos;
	t_philo			*philo;
	int				i;

	i = 0;
	while (i < NUMBER_OF_LOCKS)
		error = (pthread_mutex_destroy(pdata->shared_locks + i++) || error);
	while (fork < lastf)
		error = (pthread_mutex_destroy(&fork++->lock) || error);
	philo = pdata->philo;
	while (philo < lastp)
		error = (pthread_mutex_destroy(&philo++->access) || error);
	pdata->exit_status = (pdata->exit_status || error);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct s_contrl	contrl;
	struct s_philo	*philo;

	data.contrl = &contrl;
	if (!load_sim(&data, --argc, ++argv))
	{
		data.exit_status = (pthread_join(data.contrl->thread, NULL)
				|| data.contrl->flags & PHILO_ERR);
		philo = data.philo + data.number_of_philos;
		while (philo-- > data.philo)
			pthread_detach(philo->thread);
		destroy_locks(&data, data.fork, 0);
	}
	free(data.shared_locks);
	free(data.fork);
	free(data.philo);
	return (data.exit_status);
}
