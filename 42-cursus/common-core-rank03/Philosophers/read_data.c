/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:48:44 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/25 10:03:39 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static int	isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static int	atoi3(const char *str, int *n, const int min)
{
	int	i;
	int	sg;

	while (isspace(*str))
		str++;
	sg = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	*n = 0;
	while (isdigit(*str))
	{
		i = *str++ - '0';
		if ((sg && *n < (INT_MIN + i) / 10) || (!sg && *n > (INT_MAX - i) / 10))
			return (1);
		if (sg)
			*n = 10 * *n - i;
		else
			*n = 10 * *n + i;
	}
	if (*str || *n < min)
		return (1);
	return (0);
}

int	read_data(int param, char **args, struct s_data *pdata, int *status)
{
	*status = param < 4 || param > 5
		|| atoi3(*args++, &pdata->number_of_philosophers, 1)
		|| atoi3(*args++, &pdata->time_to_die, 0)
		|| atoi3(*args++, &pdata->time_to_eat, 0)
		|| atoi3(*args++, &pdata->time_to_sleep, 0)
		|| (param == 5
			&& atoi3(*args, &pdata->number_of_times_each_philosopher_must_eat,
				0));
	return (*status);
}
