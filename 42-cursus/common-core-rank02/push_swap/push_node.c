/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:53:26 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/14 19:11:49 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_node(t_node **ppath, t_info *pinfo, enum e_ops op, int *status)
{
	const size_t	size = pinfo->size_node;
	t_node *const	node = pinfo->temp_nodes0;
	t_node			*next;

	if (*ppath
		&& (*ppath)->moves % DEFAULT_BATCH_SZE != DEFAULT_BATCH_SZE - 1)
		next = *ppath + size;
	else
		next = malloc(DEFAULT_BATCH_SZE * size);
	if (!next)
	{
		*status = MEM_ERR;
		return ;
	}
	ft_memcpy(next, node, size);
	next->camefrom = *ppath;
	if (*ppath)
		next->moves = (*ppath)->moves + 1;
	next->camewith = op;
	*ppath = next;
	*status = SUCCESS;
}
