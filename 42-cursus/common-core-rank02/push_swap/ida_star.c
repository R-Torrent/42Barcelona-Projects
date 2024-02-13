/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ida_star.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:33:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/13 18:36:35 by rtorrent         ###   ########.fr       */
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
	i = node->n[A];
	while (++i < n)
		if (node->stacks[i] < node->stacks[i - 1])
			h_b++;
	if (h_a < h_b)
		return (h_b);
	else
		return (h_a);
}

unsigned int	search(t_node **ppath, unsigned int bound, t_info *pinfo,
	int *status)
{
	unsigned int	estimation;
	unsigned int	minimum;
	unsigned int	threshold;
	enum e_ops		successor;

	estimation = (*ppath)->moves + heuristic(*ppath, pinfo->n_args);
	if (estimation > bound || estimation > INFINITE || *status != WORKING
		|| is_goal(*ppath, status))
		return (estimation);
	minimum = UINT_MAX;
	successor = SA;
	while (successor < ID)
	{
		if (!in_path(*ppath, operate_stacks(*ppath, successor++, pinfo)))
		{
			push_node(ppath, pinfo->temp_nodes, pinfo->size_node, status);
			threshold = search(ppath, bound, pinfo, status);
			if (*status != WORKING)
				return (estimation);
			if (threshold < minimum)
				minimum = threshold;
			pop_node(ppath);
		}
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
	pinof->status = WORKING;
	while (true)
	{
		threshold = search(ppath, bound, pinfo, &status);
		if (pinfo->status != WORKING)
			return (pinfo->status);
		if (threshold > INFINITE)
			return (NOT_FND);
		bound = threshold;
	}
}
