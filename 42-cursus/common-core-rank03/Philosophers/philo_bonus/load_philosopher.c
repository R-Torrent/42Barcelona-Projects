/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_philosopher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:51 by rtorrent          #+#    #+#             */
/*   Updated: 2024/08/07 03:07:46 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_obituary(t_contrl *contrl, t_philo *philo)
{
	t_data *const	pdata = contrl->pdata;

	if (sem_wait(philo->access))
		contrl->ret |= PHILO_ERR;
	else if (contrl->elapsed - philo->last_meal >= pdata->time_to_die)
	{
		if (sem_wait(pdata->shared_sems[PRINT])
			|| !printf("%s %i died\n", contrl->timestamp, philo->n)
			|| sem_post(pdata->shared_sems[PRINT]))
			contrl->ret |= PHILO_ERR;
		contrl->ret |= TERMINATE;
		if (sem_post(pdata->shared_sems[TERMN]))
			contrl->ret |= PHILO_ERR;
	}
	if (sem_post(philo->access))
		contrl->ret |= PHILO_ERR;
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
		contrl->ret |= PHILO_ERR;
	while (!contrl->ret)
	{
		err = sem_post(pdata->philo->access);
		print_obituary(contrl, pdata->philo);
		tstamp(contrl);
		wait_usec(contrl, 1000 - contrl->elapsed % 1000, 1);
		err = (sem_wait(pdata->philo->access) || err);
		if (err)
			contrl->ret |= PHILO_ERR;
	}
	if (sem_post(pdata->philo->access))
		contrl->ret |= PHILO_ERR;
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

int	load_philo(t_philo *philo)
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
	err = (err || pthread_create(&philo->contrl->thread_controller, NULL,
				(void *)run_contrl, philo->contrl)
			|| pthread_create(&philo->thread_philo, NULL,
				(void *)run_philo, philo)
			|| sem_wait(philo->contrl->pdata->shared_sems[TERMN])
			|| sem_wait(philo->access));
	philo->contrl->ret |= TERMINATE;
	err = (sem_post(philo->access) || err);
	err = (sem_post(philo->contrl->pdata->shared_sems[TERMN]) || err);
	err = (sem_post(philo->contrl->pdata->shared_sems[FORKS]) || err);
	err = (pthread_join(philo->thread_philo, NULL) || err);
	return (pthread_join(philo->contrl->thread_controller, NULL) || err);
}
