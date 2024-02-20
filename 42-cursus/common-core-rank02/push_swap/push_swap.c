/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:11:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/20 20:19:49 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_path(t_node *path)
{
	if (path->camefrom)
		print_path(path->camefrom);
	if (path->camewith != ID)
		ft_putendl_fd(op_string(path->camewith), 1);
}

void	pop_node(t_node **ppath)
{
	t_node *const	top = *ppath;

	if (*ppath)
	{
		*ppath = (*ppath)->camefrom;
		if (!(top->moves % DEFAULT_BATCH_SZE))
			free(top);
	}
}

void	push_node(t_node **ppath, t_info *pinfo, int *pstatus)
{
	t_node	*next;

	if (*ppath
		&& (*ppath)->moves % DEFAULT_BATCH_SZE != DEFAULT_BATCH_SZE - 1)
		next = (t_node *)((char *)*ppath + pinfo->size_node);
	else
		next = malloc(DEFAULT_BATCH_SZE * pinfo->size_node);
	if (!next)
	{
		*pstatus = MEM_ERR;
		return ;
	}
	ft_memcpy(next, pinfo->temp0, pinfo->size_node);
	next->camefrom = *ppath;
	if (*ppath)
		next->moves = (*ppath)->moves + 1;
	*ppath = next;
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_node	*path;
	int		status;

	if (!--argc)
		exit(SUCCESS);
	path = NULL;
	status = init_root(&info, (unsigned int)argc, argv);
	if (status == WORKING)
		push_node(&path, &info, &status);
	if (status == WORKING)
	{
		if (argc <= MAX_EXACT)
			ida_star(&path, &info, &status);
		else
			aprox(&path, &info, &status);
	}
	if (!status)
		print_path(path);
	else
		ft_putendl_fd("Error", 2);
	while (path)
		pop_node(&path);
	free(info.temp0);
	exit(status);
}
