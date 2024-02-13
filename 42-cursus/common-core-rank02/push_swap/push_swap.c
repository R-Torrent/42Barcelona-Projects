/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:11:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/13 23:44:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_path(t_node *path)
{
	static char	*ops[] = {"SA", "SB", "SS", "PA", "PB", "RA", "RB", "RR", "RRA",
		"RRB", "RRR", "ID"};

	if (path->camefrom)
		print_path(path->camefrom);
	if (path->camewith != ID)
		ft_putendl_fd(ops[path->camewith], 1);
}

int	fill_root(t_node *root, const int *src, size_t size)
{
	const int *const	src_0 = src;
	const int *const	src_n = src + size;
	const int			*src_current;

	root->camefrom = NULL;
	root->camewith = ID;
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

int	init_root(t_node **ppath, t_node *root, unsigned int n, char *args[])
{
	int		status;
	int		*args_n;
	size_t	i;

	status = SUCCESS;
	if (n > SIZE_MAX >> 1)
		status = MEM_ERR;
	*ppath = NULL;
	args_n = malloc(n * sizeof(int));
	if (!args_n)
		status = MEM_ERR;
	i = 0;
	while (!status && i < n)
		args_n[i++] = atoi2(*++args, &status);
	if (!status)
		status = fill_root(root, args_n, n);
	free(args_n);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_node	*path;
	int		status;

	if (!--argc)
		exit(SUCCESS);
	info.n_args = (size_t)argc;
	info.size_node = sizeof(t_node) + argc * sizeof(size_t);
	info.temp_nodes0 = ft_calloc(2, info.size_node);
	info.temp_nodes1 = (t_node *)((char *)info.temp_nodes0 + info.size_node);
	status = init_root(&path, info.temp_nodes0, (unsigned int)argc, argv);
	if (!status)
		push_node(&path, info.temp_nodes0, info.size_node, &status);
	if (!status)
		status = ida_star(&path, &info);
	if (!status)
		print_path(path);
	else
		ft_putendl_fd("Error", 2);
	while (path)
		pop_node(&path);
	free(info.temp_nodes0);
	exit(status);
}
