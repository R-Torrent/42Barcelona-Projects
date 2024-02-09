/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:03:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/09 11:03:55 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	fill_root(t_node *root, const int *src, int size)
{
	const int *const	src_0 = src;
	const int *const	src_n = src + size;
	const int 			*src_current;

	root->camewith = ID;
	while (size--)
	{
		src = src_0;
		src_current = src0 + size;
		while (src < src_n)
		{
			if (*src < src_current)
				root->stacks[root->na++]++;
			else if (src != src_current && *src == *src_current)
				return (DUP_ERR);
			src++;
		}
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

int	init_root(t_node **proot, int n, char *args[])
{
	int		status;
	int 	*args_n;
	size_t	i;

	status = SUCCESS;
	if (n > SIZE_MAX >> 1)
		status = MEM_ERR;
	args_n = malloc(n * sizeof(int));
	*proot = ft_calloc(1, sizeof(t_node) + n * sizeof(unsigned int));
	if (!args_n || !*proot)
		status = MEM_ERR;
	i = 0;
	while (!status && i < n)
		args_n[i++] = atoi2(*++args, &status);
	if (!status)
		status = fill_root(*proot, args_n, n);
	if (
	free(args_n);
	return (status);
}
