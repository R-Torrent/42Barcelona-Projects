/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ida_star.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:33:53 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/09 01:51:35 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	**find_successors(const t_step *node)
{
	t_step **const	p = malloc(2* ID * sizeof(t_step *));
	enum e_ops		op;

	if (p)
	{
		op = SA;
		while (op < ID)
		{
			p[op<<1] = ft_stadup(node->a, dup)
			p[op<<1 + 1] = ft_stadup(node->b, dup)
			if (!p[op<<1] || !p{
			op++;
		}
		if (ft_stasize(node->a))
		{
			ft_stapush(p[PB<<1 + 1], ft_stapop(p[PB<<1]));
			if (ft_stasize(node->a) > 1)
			{
				ft_staswap(p[SA<<1]);
				ft_staswap(p[SS<<1]);
				ft_staroll_right(p[RA<<1]);
				ft_staroll_right(p[RR<<1]);
				ft_staroll_left(p[RRA<<1]);
				ft_staroll_left(p[RRR<<1]);
			}
		}
		if (ft_stasize(node->b))
		{
			ft_stapush(p[PA<<1], ft_stapop(p[PA<<1 + 1]));
			if (ft_stasize(node->b) > 1)
			{
				ft_staswap(p[SB<<1 + 1]);
				ft_staswap(p[SS<<1 + 1]);
				ft_staroll_right(p[RB<<1 + 1]);
				ft_staroll_right(p[RR<<1 + 1]);
				ft_staroll_left(p[RRB<<1 + 1]);
				ft_staroll_left(p[RRR<<1 + 1]);
			}
		}
	}
	return (p);
}

bool	search(t_stack path, const t_stack *target, unsigned int *bound)
{
	t_step *const		last_node = ft_stapeek(path);
	const unsigned int	cost = ft_stasize(path) - 1 + heuristic(last_node);
	unsigned int		min;

	if (cost > *bound)
	{
		*bound = cost;
		return (false);
	}
	if (ft_stamatch(target, last_node->a))
		return (true);
	min = UINT_MAX;
	find_successors(last_node);
}

void	ida_star(t_stack *path, const t_stack *target)
{
	unsigned int	bound;

	bound = heuristic(ft_stapeek(path));
	while (true)
		if (search(path, &bound))
		{
			ft_staiter(path, print_path);
			return (SUCCESS);
		}
		else if (bound == -1)
			return (MEM_ERR);
}
		
