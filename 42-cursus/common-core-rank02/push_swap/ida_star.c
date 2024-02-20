/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ida_star.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:33:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/20 20:19:58 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	in_path(t_node *path, t_info *pinfo)
{
	size_t	i;

	if (!path)
		return (false);
	if (!path->camefrom || !in_path(path->camefrom, pinfo))
	{
		if (path->n[A] != pinfo->temp0->n[A])
			return (false);
		i = 0;
		while (i < pinfo->n_args)
		{
			if (path->stacks[i] != pinfo->temp0->stacks[i])
				return (false);
			i++;
		}	
	}
	return (true);
}

bool	try_successor(t_node *path, enum e_ops succ, t_info *pinfo)
{
	const enum e_ops	ins = path->camewith;

	if ((succ == SA && path->n[A] < 2) || (succ == SB && path->n[B] < 2)
		|| (succ == SS && (path->n[A] < 2 || path->n[B] < 2))
		|| (succ == PA && !path->n[B]) || (succ == PB && !path->n[A])
		|| ((succ == RA || succ == RRA) && path->n[A] < 3)
		|| ((succ == RB || succ == RRB) && path->n[B] < 3)
		|| ((succ == RR || succ == RRR) && (path->n[A] < 2 || path->n[B] < 2
				|| pinfo->n_args == 4)))
		return (false);
	if (((succ == SA || succ == SB || succ == SS)
			&& (ins == SA || ins == SB || ins == SS))
		|| (succ == PA && ins == PB) || (succ == PB && ins == PA)
		|| (succ == RA && (ins == RRA || ins == RRR || ins == RB))
		|| (succ == RB && (ins == RRB || ins == RRR || ins == RA))
		|| (succ == RRA && (ins == RA || ins == RR || ins == RRB))
		|| (succ == RRB && (ins == RB || ins == RR || ins == RRA))
		|| (succ == RR && (ins == RRR || ins == RRA || ins == RRB))
		|| (succ == RRR && (ins == RR || ins == RA || ins == RB)))
		return (false);
	return (!in_path(path->camefrom, op_stacks(path, succ, pinfo)));
}

/* ************************************************************************** */
/*                                                                            */
/*   Heuristic cost: max{unordered consecutive entries on stack 'a', ordered  */
/*   consecutive entries in stack 'b'} (a PA command will reverse ordering    */
/*   of the latter) + number of elements in stack 'b' + possibly an extra     */
/*   move if the top of stack 'b' > top of stack 'a'.                         */
/*                                                                            */
/* ************************************************************************** */

unsigned int	heuristic(t_node *node, size_t n)
{
	unsigned int	h_a;
	unsigned int	h_b;
	size_t			i;

	h_a = node->n[B];
	i = 0;
	while (++i < node->n[A])
		if (node->stacks[i] > node->stacks[i - 1])
			h_a++;
	h_b = node->n[B];
	if (node->stacks[n - 1] > node->stacks[i - 1])
	{
		h_a++;
		h_b++;
	}	
	while (++i < n)
		if (node->stacks[i] < node->stacks[i - 1])
			h_b++;
	if (h_a < h_b)
		return (h_b);
	else
		return (h_a);
}

unsigned int	search(t_node **ppath, unsigned int bound, t_info *pinfo,
	int *pstatus)
{
	unsigned int	estimate;
	unsigned int	minimum;
	unsigned int	threshold;
	enum e_ops		successor;

	estimate = (*ppath)->moves + heuristic(*ppath, pinfo->n_args);
	if (estimate > bound || estimate > LIMIT || is_goal(*ppath, pinfo, pstatus))
		return (estimate);
	minimum = UINT_MAX;
	successor = SA;
	while (successor < ID)
	{
		if (try_successor(*ppath, successor, pinfo))
		{
			push_node(ppath, pinfo, pstatus);
			threshold = search(ppath, bound, pinfo, pstatus);
			if (*pstatus != WORKING)
				return (estimate);
			if (threshold < minimum)
				minimum = threshold;
			pop_node(ppath);
		}
		successor++;
	}
	return (minimum);
}

/* ************************************************************************** */
/*                                                                            */
/*   Search algorithm: Iterative deepening A* (IDA*)                          */
/*   More information: https://en.wikipedia.org/wiki/Iterative_deepening_A*   */
/*                                                                            */
/* ************************************************************************** */

void	ida_star(t_node **ppath, t_info *pinfo, int *pstatus)
{
	unsigned int	bound;
	unsigned int	threshold;

	bound = heuristic(*ppath, pinfo->n_args);
	while (true)
	{
		threshold = search(ppath, bound, pinfo, pstatus);
		if (*pstatus != WORKING)
			break ;
		if (threshold > LIMIT)
		{
			*pstatus = NOT_FND;
			break ;
		}
		bound = threshold;
	}
}
