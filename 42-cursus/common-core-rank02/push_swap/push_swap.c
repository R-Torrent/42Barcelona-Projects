/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:11:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 20:29:20 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	delstep(t_step *step)
{
	ft_staclear(step->a, free);
	ft_staclear(step->b, free);
	free(step->a);
	free(step->b);
	free(step);
}

void	free_memory(t_stack *const path, t_stack *const a, t_stack *const b)
{
	if (!path || ft_staisempty(path))
	{
		ft_staclear(a, free);
		ft_staclear(b, free);
		free(a);
		free(b);
	}
	else
		ft_staclear(path, (void (*)(void *))delstep);
	free(path);
}

t_step	*fill_start(t_stack *const a, t_stack *const b)
{
	t_step *const	start = malloc(sizeof(t_step));

	if (start)
	{
		start->a = a;
		start->b = b;
		start->camewith = ID;
	}
	return (start);
}

int	main(int argc, char *argv[])
{
	int		status;
	t_stack	*a;
	t_stack	*b;
	t_stack	*path;
	t_step	*start;

	if (argc == 1)
		exit(SUCCESS);
	status = init_stacks(&a, &b, argc - 1, argv);
	if (!status)
	{
		path = ft_stanew(0);
		start = fill_start(a, b);
		if (!ft_stapush(path, start))
		{
			status = MEM_ERR;
			free(start);
		}
	}
	if (!status)
		; // ********* CONTINUE HERE
	else
		ft_putendl_fd("Error", 2);
	free_memory(path, a, b);
	exit(status);
}
