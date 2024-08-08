/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_philosopher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:51 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/08 17:00:14 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	force_kill_signal(t_data *pdata)
{
	int	n;

	n = pdata->number_of_philos;
	while (n--)
		sem_post(pdata->shared_sems[MLSOK]);
	sem_wait(pdata->shared_sems[MASTR]);
	sem_wait(pdata->shared_sems[MASTR]);
}

static void	print_obituary(t_contrl *contrl, t_philo *philo)
{
	t_data *const	pdata = contrl->pdata;

	if (sem_wait(philo->access))
		contrl->err = 1;
	else if (contrl->elapsed - philo->last_meal >= pdata->time_to_die)
	{
		if (sem_wait(pdata->shared_sems[PRINT]))
			contrl->err = 1;
		printf("%s %i died\n", contrl->timestamp, philo->n);
		force_kill_signal(pdata);
	}
	if (sem_post(philo->access))
		contrl->err = 1;
}

// main loop runs once every millisecond
static void	run_contrl(t_contrl *contrl)
{
	t_data *const	pdata = contrl->pdata;
	int				err;

	err = (sem_wait(pdata->shared_sems[MASTR])
			|| sem_post(pdata->shared_sems[MASTR]));
	err = (sem_wait(pdata->philo->access) || err);
	if (err)
		contrl->err = 1;
	while (!contrl->err)
	{
		err = sem_post(pdata->philo->access);
		print_obituary(contrl, pdata->philo);
		wait_usec(contrl, 1000 - contrl->elapsed % 1000, 1);
		err = (sem_wait(pdata->philo->access) || err);
		if (err)
			contrl->err = 1;
	}
	sem_post(pdata->philo->access);
}

static char	*sem_name(char *sname, int n, const char *suffix)
{
	char *const	sname0 = sname;

	place_digit((unsigned int)n, &sname);
	*sname++ = '.';
	while (*suffix)
		*sname++ = *suffix++;
	*sname = '\0';
	return (sname0);
}

void	load_philo(t_philo *philo)
{
	char	sname[2][20];
	int		err;

	philo->access = sem_open(sem_name(sname[0], philo->n, "ACCESS"),
			S_OFLAG, S_MODE, 1);
	philo->read_time = sem_open(sem_name(sname[1], philo->n, "RDTIME"),
			S_OFLAG, S_MODE, 1);
	err = (philo->access == SEM_FAILED || sem_unlink(sname[0]));
	err = (philo->read_time == SEM_FAILED || sem_unlink(sname[1]) || err);
	if (!philo->meals_left)
		err = (sem_post(philo->contrl->pdata->shared_sems[MLSOK]) || err);
	if (!(err || pthread_create(&philo->thread_philo, NULL, (void *)run_philo,
				philo) || pthread_detach(philo->thread_philo)))
		run_contrl(philo->contrl);
}
