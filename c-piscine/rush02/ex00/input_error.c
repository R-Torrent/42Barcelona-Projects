/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:52:40 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/16 22:53:37 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static void	print_error(void)
{
	write(1, "Error\n", 6);
}

int	check_input(int argc, char *argv[], int *pnum, char **pfile)
{
	*pnum = -1;
	if (argc == 2)
	{
		*pfile = "numbers.dict";
		*pnum = ft_atou(argv[1]);
	}
	else if (argc == 3)
	{
		*pfile = argv[1];
		*pnum = ft_atou(argv[2]);
	}
	if (*pnum == -1)
	{
		print_error();
		return (ARGC_ERROR);
	}
	return (SUCCESS);
}
