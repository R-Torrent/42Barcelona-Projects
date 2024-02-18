/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:25:18 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/18 22:51:46 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*rotate_right(t_node *dst, const t_node *src, enum e_stacks st,
	t_info *pinfo)
{
	size_t	i;
	size_t	j;
	size_t	top;

	ft_memcpy(dst, src, pinfo->size_node);
	if (src->n[st] >= 2)
	{
		if (st == A)
		{
			i = dst->n[A] - 1;
			j = 0;
		}
		else
		{
			i = pinfo->n_args - 1;
			j = dst->n[A];
		}
		top = dst->stacks[i];
		while (i-- > j)
			dst->stacks[i + 1] = dst->stacks[i];
		dst->stacks[j] = top;
	}
	return (dst);
}

t_node	*rotate_left(t_node *dst, const t_node *src, enum e_stacks st,
	t_info *pinfo)
{
	size_t	i;
	size_t	j;
	size_t	bottom;

	ft_memcpy(dst, src, pinfo->size_node);
	if (src->n[st] >= 2)
	{
		if (st == A)
		{
			i = 0;
			j = dst->n[A];
		}
		else
		{
			i = dst->n[A];
			j = pinfo->n_args;
		}
		bottom = dst->stacks[i];
		while (++i < j)
			dst->stacks[i - 1] = dst->stacks[i];
		dst->stacks[i - 1] = bottom;
	}
	return (dst);
}

t_node	*push(t_node *dst, const t_node *src, enum e_stacks st, t_info *pinfo)
{
	ft_memcpy(dst, src, pinfo->size_node);
	if (!src->n[!st])
		return (ft_memcpy(pinfo->temp0, dst, pinfo->size_node));
	if (st == A)
	{
		rotate_right(pinfo->temp0, dst, B, pinfo);
		pinfo->temp0->n[A]++;
		pinfo->temp0->n[B]--;
	}
	else
	{
		dst->n[A]--;
		dst->n[B]++;
		rotate_left(pinfo->temp0, dst, B, pinfo);
	}
	return (pinfo->temp0);
}

t_node	*swap(t_node *dst, const t_node *src, enum e_stacks st, t_info *pinfo)
{
	size_t	i;
	size_t	swap;

	ft_memcpy(dst, src, pinfo->size_node);
	if (src->n[st] >= 2)
	{
		if (st == A)
			i = dst->n[A] - 1;
		else
			i = pinfo->n_args - 1;
		swap = dst->stacks[i];
		dst->stacks[i] = dst->stacks[i - 1];
		dst->stacks[i - 1] = swap;
	}
	return (dst);
}

t_info	*operate_stacks(const t_node *node, enum e_ops op, t_info *pinfo)
{
	if (op == SA)
		swap(pinfo->temp0, node, A, pinfo);
	else if (op == SB)
		swap(pinfo->temp0, node, B, pinfo);
	else if (op == SS)
		swap(pinfo->temp0, swap(pinfo->temp1, node, A, pinfo), B, pinfo);
	else if (op == PA)
		push(pinfo->temp1, node, A, pinfo);
	else if (op == PB)
		push(pinfo->temp1, node, B, pinfo);
	else if (op == RA)
		rotate_right(pinfo->temp0, node, A, pinfo);
	else if (op == RB)
		rotate_right(pinfo->temp0, node, B, pinfo);
	else if (op == RR)
		rotate_right(pinfo->temp0,
			rotate_right(pinfo->temp1, node, A, pinfo), B, pinfo);
	else if (op == RRA)
		rotate_left(pinfo->temp0, node, A, pinfo);
	else if (op == RRB)
		rotate_left(pinfo->temp0, node, B, pinfo);
	else
		rotate_left(pinfo->temp0,
			rotate_left(pinfo->temp1, node, A, pinfo), B, pinfo);
	return (pinfo);
}
