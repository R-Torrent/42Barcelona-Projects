/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:23:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/10 02:11:48 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*pop_node(t_node **ppath, t_node *node, size_t size_node)
{
	t_node *const	top = *ppath;

	if (*ppath)
	{
		*ppath = (*ppath)->camefrom;
		ft_memcpy(node, top, size_node);
		if (!(top->moves % DEFAULT_BATCH_SZE))
			free(top);
	}
	return (*ppath);
}
