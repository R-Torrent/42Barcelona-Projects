/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:03:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/17 21:30:35 by rtorrent         ###   ########.fr       */
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

bool	get_ins(char **pinstruction, int *pstatus)
{
	char	*c;

	*pinstruction = ft_getnextline_fd(1);
	if (*pinstruction)
	{
		c = ft_strchr(*pinstruction, '\n');
		if (c)
			*c = '\0';
		return (true);
	}
	*pstatus = NOT_FND;
	return (false);
}

void	run_ins(t_node *node, t_info *pinfo, int *pstatus)
{
	char		*instruction;
	enum e_ops	op;

	if (is_goal(node, pinfo, pstatus))
		return ;
	if (get_ins(&instruction, pstatus) && get_op(&op, instruction, pstatus))
		operate_stacks(node, op, pinfo);
	free(instruction);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_node	*progress;
	int		status;

	if (!--argc)
		exit(SUCCESS);
	status = init_root(&info, (unsigned int)argc, argv);
	progress = malloc(info.size_node);
	if (!progress && status == WORKING)
		status = MEM_ERR;
	while (status == WORKING)
		run_ins(ft_memcpy(progress, info.temp_nodes0, info.size_node),
			&info, &status);
	if (status == SUCCESS)
		ft_putendl_fd("OK", 1);
	else if (status == NOT_FND)
		ft_putendl_fd("KO", 1);
	else
		ft_putendl_fd("Error", 2);
	free(progress);
	free(info.temp_nodes0);
	exit(status);
}
