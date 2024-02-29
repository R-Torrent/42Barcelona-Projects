/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:03:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/29 02:33:52 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	run_ins(t_info *pinfo, int *pstatus)
{
	char *const	instruction = ft_getnextline_fd(0);
	char		*c;
	enum e_ops	op;

	if (instruction)
	{
		c = ft_strchr(instruction, '\n');
		if (c)
			*c = '\0';
		op = SA;
		while (op < ID)
		{
			if (!ft_strncmp(op_string(op), instruction, 3))
				break ;
			op++;
		}
		if (op < ID)
			op_stacks(pinfo->temp0, op, pinfo);
		else
			*pstatus = UNK_INS;
	}
	else if (!is_goal(pinfo->temp0, pinfo, pstatus))
		*pstatus = NOT_FND;
	free(instruction);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	int		status;

	if (!--argc)
		exit(SUCCESS);
	status = init_root(&info, (unsigned int)argc, argv);
	while (status == WORKING)
		run_ins(&info, &status);
	if (status == SUCCESS)
		ft_putendl_fd("OK", 1);
	else if (status == NOT_FND)
		ft_putendl_fd("KO", 1);
	else
		ft_putendl_fd("Error", 2);
	free(info.temp0);
	exit(status);
}
