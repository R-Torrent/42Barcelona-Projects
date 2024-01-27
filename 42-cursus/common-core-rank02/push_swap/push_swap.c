/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:11:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/28 00:13:38 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	delstep(t_step *step)
{
	free(step->a);
	free(step->b);
	free(step);
}

void	free_memory(const int status, t_bst *const tree, t_stack *const sta,
	t_stack *const stb)
{
	if (tree)
	{
		ft_bstclear(tree, (void (*)(void *))delstep);
		free(tree);
	}
	if (status)
	{
		free(sta);
		free(stb);
	}
}

t_step	*fill_root(t_stack *const sta, t_stack *const stb)
{
	t_step *const	step0 = malloc(sizeof(t_step));

	if (step0)
	{
		step0->a = sta;
		step0->b = stb;
		step0->camefrom = NULL;
		step0->camewith = ID;
		step0->visited = false;
	}
	return (step0);
}

int	compf(const t_step *step1, const t_step *step2)
{
	int		res;
	size_t	i;

	res = step1->a->n - step2->a->n;
	if (res)
		return (res);
	i = 0;
	while (i < step1->a->n)
	{
		res = step1->a->stack[i] - step2->a->stack[i];
		if (res)
			return (res);
	}
	i = 0;
	while (i < step1->b->n)
	{
		res = step1->b->stack[i] - step2->b->stack[i];
		if (res)
			return (res);
	}
	return (0);
}	

int	main(int argc, char *argv[])
{
	int		status;
	t_bst	*tree;
	t_stack	*sta;
	t_stack	*stb;
	t_step	*step0;

	if (argc == 1)
		exit(SUCCESS);
	status = init_stacks(&sta, &stb, argc - 1, argv);
	if (!status)
	{
		tree = ft_bstnew(NULL, (int (*)(const void *, const void *))compf);
		step0 = fill_root(sta, stb);
		if (!ft_bstinsert(tree, step0))
		{
			status = MEM_ERR;
			free(step0);
		}
	}
	free_memory(status, tree, sta, stb);
	if (status)
		ft_putendl_fd("Error", 2);
	exit(status);
}
