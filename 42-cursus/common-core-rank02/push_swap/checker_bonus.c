/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:03:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/29 01:41:51 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

bool	get_op(enum e_ops *pop, const char *instruction, int *pstatus)
{
	*pop = SA;
	while (*pop < ID)
	{
		if (!ft_strncmp(op_string(*pop), instruction, 3))
			return (true);
		(*pop)++;
	}
	*pstatus = UNK_INS;
	return (false);
}

bool	get_ins(char **pinstruction)
{
	char	*c;

	*pinstruction = ft_getnextline_fd(0);
	if (*pinstruction)
	{
		c = ft_strchr(*pinstruction, '\n');
		if (c)
			*c = '\0';
	}
	return (*pinstruction);
}

void	run_ins(t_info *pinfo, int *pstatus)
{
	char		*instruction;
	enum e_ops	op;

	if (get_ins(&instruction) && get_op(&op, instruction, pstatus))
		op_stacks(pinfo->temp0, op, pinfo);
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
