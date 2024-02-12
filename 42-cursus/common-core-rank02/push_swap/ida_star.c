/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ida_star.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:33:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/12 18:33:59 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* ************************************************************************** */
/*                                                                            */
/*   Search algorithm: Iterative deepening A* (IDA*)                          */
/*   More information: https://en.wikipedia.org/wiki/Iterative_deepening_A*   */
/*                                                                            */
/* ************************************************************************** */

unsigned int	search(t_node **ppath, unsigned int bound, t_node *temp_nodes,
	int *status)
{
	(void)ppath;
	(void)bound;
	(void)temp_nodes;
	*status = SUCCESS;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*   Heuristic cost: unordered, consecutive integers on stack 'a' + ordered,  */
/*   consecutive integers in stack 'b' (a PA command will reverse ordering)   */
/*   + number of elements in stack 'b'                                        */
/*                                                                            */
/* ************************************************************************** */

unsigned int	heuristic(t_node *node, size_t n)
{
	unsigned int	h;
	size_t			i;

	h = node->n[B];
	i = 0;
	while (++i < node->n[A])
		if (node->stacks[i] > node->stacks[i - 1])
			h++;
	i = node->n[A];
	while (++i < n)
		if (node->stacks[i] < node->stacks[i -1])
			h++;
	return (h);
}

int	ida_star(t_node **ppath, size_t n, t_node *temp_nodes)
{
	unsigned int	bound;
	unsigned int	threshold;
	int				status;

	bound = heuristic(*ppath, n);
	while (true)
	{
		threshold = search(ppath, bound, temp_nodes, &status);
		if (status != WORKING)
			return (status);
		bound = threshold;
	}
}
