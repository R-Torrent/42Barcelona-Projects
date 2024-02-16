/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ida_star.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:33:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/16 23:51:22 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Heuristic cost: max{unordered consecutive entries on stack 'a', ordered  */
/*   consecutive entries in stack 'b'} (a PA command will reverse ordering    */
/*   of the latter) + number of elements in stack 'b'                         */
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

bool	in_path(t_node *path, t_node *node, t_info *pinfo)
{
	size_t	i;

	if (node && (!path->camefrom || !in_path(path->camefrom, node, pinfo)))
	{
		if (path->n[A] != node->n[A])
			return (false);
		i = 0;
		while (i < pinfo->n_args)
		{
			if (path->stacks[i] != node->stacks[i])
				return (false);
			i++;
		}	
	}
	return (true);
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
		if (!in_path(*ppath, operate_stacks(*ppath, successor, pinfo), pinfo))
		{
			push_node(ppath, pinfo, successor, pstatus);
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

int	ida_star(t_node **ppath, t_info *pinfo)
{
	unsigned int	bound;
	unsigned int	threshold;
	int				status;

	bound = heuristic(*ppath, pinfo->n_args);
	status = WORKING;
	while (true)
	{
		threshold = search(ppath, bound, pinfo, &status);
		if (status != WORKING)
			return (status);
		if (threshold > LIMIT)
			return (NOT_FND);
		bound = threshold;
	}
}
