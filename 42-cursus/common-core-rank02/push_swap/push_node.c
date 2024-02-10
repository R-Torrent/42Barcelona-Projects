/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:53:26 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/10 02:25:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*push_node(t_node **ppath, t_node *node, size_t size_node, int *status)
{
	t_node	*next;

	if (*ppath
		&& (*ppath)->moves % DEFAULT_BATCH_SZE != DEFAULT_BATCH_SZE - 1)
		next = *ppath + size_node;
	else
		next = ft_calloc(DEFAULT_BATCH_SZE, size_node);
	if (!next)
	{
		*status = MEM_ERR;
		return (NULL);
	}
	ft_memcpy(next, node, size_node);
	next->camefrom = *ppath;
	next->moves = (*ppath)->moves + 1;
	*ppath = next;
	*status = SUCCESS;
	return (*ppath);
}
