/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:53:26 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/09 13:34:32 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_node(t_node **ppath, size_t size_node, t_node *node)
{
	t_node	*next;

	if (*ppath
		&& (*ppath)->node.moves % DEFAULT_BATCH_SZE != DEFAULT_BATCH_SZE - 1)
		next = *ppath + size_node;
	else
		next = ft_calloc(DEFAULT_BATCH_SZE, size_node);
	if (!next)
		return (MEM_ERR);
	ft_memcpy(next, node, size_node);
	next->camefrom = *ppath;
	next->moves = (*ppath)->moves + 1;
	*ppath = next;
	return (SUCCESS);
}
