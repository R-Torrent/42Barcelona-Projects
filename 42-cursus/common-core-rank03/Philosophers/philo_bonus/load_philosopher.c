/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_philosopher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:51 by rtorrent          #+#    #+#             */
/*   Updated: 2024/07/18 15:03:24 by rtorrent         ###   ########.fr       */
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
	struct timeval	t[2];
	t_data *const	pdata = contrl->pdata;

	contrl->t = t;
	if (sem_wait(pdata->shared_sems[MASTR])
		|| sem_post(pdata->shared_sems[MASTR]) || gettimeofday(t, NULL))
		contrl->ret |= PHILO_ERR;
	while (!contrl->ret)
	{
		print_obituary(contrl, pdata->philo);
		tstamp(contrl);
		wait_usec(contrl, 1000 - contrl->elapsed % 1000, 1);
	}
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

	philo->access = sem_open(sem_name(sname[0], philo->n, "ACCESS"),
			S_OFLAG, S_MODE, 1);
	philo->read_time = sem_open(sem_name(sname[1], philo->n, "RDTIME"),
			S_OFLAG, S_MODE, 1);
	if (philo->access == SEM_FAILED || sem_unlink(sname[0])
		|| philo->read_time == SEM_FAILED || sem_unlink(sname[1])
		|| pthread_create(&philo->thread_philo,
			NULL, (void *)run_philo, philo)
		|| pthread_create(&philo->contrl->thread_controller,
			NULL, (void *)run_contrl, philo->contrl)
		|| pthread_detach(philo->thread_philo)
		|| sem_wait(philo->contrl->pdata->shared_sems[TERMN]))
		philo->contrl->ret |= PHILO_ERR;
	philo->contrl->ret |= TERMINATE;
	if (sem_post(philo->contrl->pdata->shared_sems[TERMN])
		|| pthread_join(philo->contrl->thread_controller, NULL))
		philo->contrl->ret |= PHILO_ERR;
	if (destroy_shared_sems(philo->contrl->pdata))
		philo->contrl->ret |= PHILO_ERR;
	if (philo->access != SEM_FAILED || sem_close(philo->access))
		philo->contrl->ret |= PHILO_ERR;
	if (philo->read_time != SEM_FAILED || sem_close(philo->read_time))
		philo->contrl->ret |= PHILO_ERR;
}
