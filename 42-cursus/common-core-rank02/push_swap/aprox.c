/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aprox.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:12:02 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/19 00:22:29 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	send_to_b(t_node **ppath, t_info *pinfo, int *pstatus)
{
	(void)ppath;
	(void)pinfo;
	(void)pstatus;
}

/* ************************************************************************** */
/*                                                                            */
/*   Search algorithm: "Mechanical Turk"                                      */
/*   More information: https://medium.com/@ayogun/push-swap-c1f5d2d41e97      */
/*                                                                            */
/*   This program deviates from the published algorithm in that a) all values */
/*   in stack 'a' are pushed to stack 'b' and b) ties among candidates in 'a' */
/*   are resolved in favour of the biggest value.                             */
/*                                                                            */
/* ************************************************************************** */

void	aprox(t_node **ppath, t_info *pinfo, int *pstatus)
{
	while ((*ppath)->n[A] && *pstatus == WORKING)
		send_to_b(ppath, pinfo, pstatus);
	while ((*ppath)->stacks[pinfo->n_args - 1] && *pstatus == WORKING)
	{
		if ((*ppath)->stacks[0] >= pinfo->n_args / 2)
			push_node(ppath, operate_stacks(*ppath, RB, pinfo), RB, pstatus);
		else
			push_node(ppath, operate_stacks(*ppath, RRB, pinfo), RRB, pstatus);
	}
	while ((*ppath)->n[B] && *pstatus == WORKING)
		push_node(ppath, operate_stacks(*ppath, PA, pinfo), PA, pstatus);
	is_goal(*ppath, pinfo, pstatus);
}
