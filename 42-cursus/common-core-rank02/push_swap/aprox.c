/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aprox.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:12:02 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/20 00:35:23 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	det_rots(size_t idxa, t_cand *pcand, size_t *rots_a, size_t *rots_b)
{
	t_cand		opts[4];
	enum e_rot	rot;

	if (rots_a[0] >= rots_b[0])
		opts[DIR_DIR] = (t_cand){idxa, rots_a[0],
			rots_a[0] - rots_b[0], rots_b[0], RA, RR};
	else
		opts[DIR_DIR] = (t_cand){idxa, rots_b[0],
			rots_a[0], rots_b[0] - rots_a[0], RR, RB};
	opts[DIR_REV] = (t_cand){idxa, rots_a[0] + rots_b[1],
		rots_a[0], rots_b[1], RA, RRB};
	opts[REV_DIR] = (t_cand){idxa, rots_a[1] + rots_b[0],
		rots_a[1], rots_b[0], RRA, RB};
	if (rots_a[1] >= rots_b[1])
		opts[REV_REV] = (t_cand){idxa, rots_a[1],
			rots_a[1] - rots_b[1], rots_b[1], RRA, RRR};
	else
		opts[REV_REV] = (t_cand){idxa, rots_b[1],
			rots_a[1], rots_b[1] - rots_a[1], RRR, RRB};
	rot = DIR_DIR;
	*pcand = opts[rot];
	while (++rot <= REV_REV)
		if (opts[rot].rots_t < (*pcand).rots_t)
			*pcand = opts[rot];
}

size_t	find_lower(size_t *n, size_t idxa)
{
	(void) n;
	return (idxa); // *** WORKING HERE
}

void	check_candidate(size_t *n, size_t idxa, t_cand *pcand)
{
	size_t			rots_a[2];
	size_t			rots_b[2];
	const size_t	idxb = find_lower(n, idxa);

	rots_a[0] = n[A] - 1 - idxa;
	rots_a[1] = 0;
	if (n[A] > 1)
		rots_a[1] = idxa + 1;
	rots_b[0] = 0;
	rots_b[1] = 0;
	if (n[B] > 1)
	{
		rots_b[0] = n[B] - 1 - idxb;
		rots_b[1] = idxb + 1;
	}
	det_rots(idxa, pcand, rots_a, rots_b);
}

void	send_to_b(t_node **ppath, t_info *pinfo, int *pstatus)
{
	size_t	elem_a;
	t_cand	cand;
	t_cand	min;

	elem_a = 0;
	min = (t_cand){.rots_t = pinfo->n_args};
	while (elem_a < (*ppath)->n[A])
	{
		check_candidate((*ppath)->n, elem_a++, &cand);
		if (cand.rots_t < min.rots_t || (cand.rots_t == min.rots_t
				&& (*ppath)->stacks[cand.idxa] > (*ppath)->stacks[min.idxa]))
			min = cand;
	}
	while (min.rots_1--)
		push_node(ppath, operate_stacks(*ppath, min.op_1, pinfo), min.op_1, pstatus);
	while (min.rots_2--)
		push_node(ppath, operate_stacks(*ppath, min.op_2, pinfo), min.op_2, pstatus);
	push_node(ppath, operate_stacks(*ppath, PB, pinfo), PB, pstatus);
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
	while ((*ppath)->stacks[0] && *pstatus == WORKING)
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
