/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:23:11 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/13 17:47:13 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
