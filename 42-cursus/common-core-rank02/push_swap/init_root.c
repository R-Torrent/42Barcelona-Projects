/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:09:05 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/15 23:10:59 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	return (SUCCESS);
}

int	atoi2(const char *str, int *status)
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
			*status = OOB_ERR;
		if (sgn)
			n = 10 * n - i;
		else
			n = 10 * n + i;
	}
	if (*str)
		*status = NAN_ERR;
	return (n);
}

int	init_root(t_info *pinfo, unsigned int n, char *args[])
{
	int		status;
	int		*args_n;
	size_t	i;

	status = SUCCESS;
	if (n > SIZE_MAX >> 1)
		status = MEM_ERR;
	pinfo->n_args = (size_t)n;
	pinfo->size_node = sizeof(t_node) + n * sizeof(size_t);
	pinfo->temp_nodes0 = ft_calloc(2, pinfo->size_node);
	args_n = malloc(n * sizeof(int));
	if (!pinfo->temp_nodes0 || !args_n)
		status = MEM_ERR;
	else
		pinfo->temp_nodes1 = (t_node *)((char *)pinfo->temp_nodes0
				+ pinfo->size_node);
	i = 0;
	while (!status && i < n)
		args_n[i++] = atoi2(*++args, &status);
	if (!status)
		status = fill_root(pinfo->temp_nodes0, args_n, n);
	free(args_n);
	return (status);
}
