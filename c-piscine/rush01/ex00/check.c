/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:34:37 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/09 21:16:01 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

int	check_set(int *set)
{
	int			i;
	t_factor	f;

	i = 0;
	while (i < 16)
	{
		if (i < 4 || (i < 12 && i > 7))
			f = UP_LF;
		else
			f = DW_RI;
		if (set[i] + set[i + (4 * f)] > 5 || set[i] + set[i + (4 * f)] == 2)
		{
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	print_error(void)
{
	write(1, "Error\n", 6);
}

// Input check
int	error_check(int argc, char *str, int *set)
{
	int	i;
	int	j;

	if (argc != 2)
	{
		print_error();
		return (ILLARGC);
	}
	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
		{
			if (j == 16 || (str[i + 1] != '\0' && str[i + 1] != ' '))
			{
				print_error();
				return (ILLVSTR);
			}
			set[j] = str[i] - '0';
			j++;
		}
		i++;
	}
	i = 0;
	while (i < j && 1 <= set[i] && set[i] <= 4)
		i++;
	if (i != 16)
	{
		print_error();
		return (ILLVSTR);
	}
	if (check_set(set))
	{
		print_error();
		return (SOLNOTF);
	}
	return (SUCCESS);
}
