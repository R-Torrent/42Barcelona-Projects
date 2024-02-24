/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:09:05 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/23 17:11:56 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_goal(t_node *node, t_info *pinfo, int *pstatus)
{
	size_t	i;
	size_t	*p;
	size_t	*p1;

	if (*pstatus != WORKING)
		return (true);
	p = node->stacks;
	i = pinfo->n_args;
	p1 = p + i;
	if (node->n[A] != i--)
		return (false);
	while (p < p1)
		if (*p++ != i--)
			return (false);
	*pstatus = SUCCESS;
	return (true);
}

char	*op_string(enum e_ops op)
{
	static char	*ops[] = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra",
		"rrb", "rrr", "id"};

	return (ops[op]);
}

int	fill_root(t_node *root, const int *src, size_t size)
{
	const int *const	src_0 = src;
	const int *const	src_n = src + size;
	const int			*src_current;

	root->camefrom = NULL;
	while (size--)
	{
		src = src_0;
		src_current = src_0 + size;
		while (src < src_n)
		{
			if (*src < *src_current)
				root->stacks[root->n[A]]++;
			else if (src != src_current && *src == *src_current)
				return (DUP_ERR);
			src++;
		}
		root->n[A]++;
	}
	return (WORKING);
}

int	atoi2(const char *str, int *pstatus)
{
	int		n;
	int		i;
	bool	sgn;

	while (ft_isspace(*str))
		str++;
	sgn = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	n = 0;
	while (ft_isdigit(*str))
	{
		i = *str++ - '0';
		if ((sgn && n < (INT_MIN + i) / 10) || (!sgn && n > (INT_MAX - i) / 10))
			*pstatus = OOB_ERR;
		if (sgn)
			n = 10 * n - i;
		else
			n = 10 * n + i;
	}
	if (*str)
		*pstatus = NAN_ERR;
	return (n);
}

int	init_root(t_info *pinfo, unsigned int n, char *args[])
{
	int		status;
	int		*args_n;
	size_t	i;

	status = WORKING;
	if (n > (unsigned int)(SIZE_MAX >> 1))
		status = MEM_ERR;
	pinfo->n_args = (size_t)n;
	pinfo->size_node = sizeof(t_node) + n * sizeof(size_t);
	pinfo->temp0 = ft_calloc(2, pinfo->size_node);
	args_n = malloc(n * sizeof(int));
	if (!pinfo->temp0 || !args_n)
		status = MEM_ERR;
	else
		pinfo->temp1 = (t_node *)((char *)pinfo->temp0 + pinfo->size_node);
	i = 0;
	while (status == WORKING && i < n)
		args_n[i++] = atoi2(*++args, &status);
	if (status == WORKING)
	{
		status = fill_root(pinfo->temp0, args_n, n);
		pinfo->temp0->camewith = ID;
	}
	free(args_n);
	return (status);
}
