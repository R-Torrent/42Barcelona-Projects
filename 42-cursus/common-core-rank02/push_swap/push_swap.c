/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:11:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 22:49:44 by rtorrent         ###   ########.fr       */
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

void	free_memory(t_stack *path, t_stack *target, t_stack *a, t_stack *b)
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
	ft_staclear(target, free);
	free(target);
}

t_step	*fill_start(t_stack *a, t_stack *b)
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

int	set_paths(t_stack **path, t_stack **target, t_stack *a, t_stack *b)
{
	t_step			*start;
	unsigned int	size;	
	unsigned int	*ordinal;

	size = ft_stasize(a);
	*path = ft_stanew(0);
	*target = ft_stanew(size);
	start = fill_start(a, b);
	if (!ft_stapush(*path, start))
	{
		free(start);
		return (MEM_ERR);
	}
	while (true)
	{
		ordinal = malloc(sizeof(unsigned int));
		if (!ft_stapush(*target, ordinal))
		{
			free(ordinal);
			return (MEM_ERR);
		}
		*ordinal = --size;
		if (!size)
			return (SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	int		status;
	t_stack	*a;
	t_stack	*b;
	t_stack	*path;
	t_stack	*target;

	if (argc == 1)
		exit(SUCCESS);
	status = init_stacks(&a, &b, argc - 1, argv);
	if (!status)
		status = set_paths(&path, &target, a, b);
	if (!status)
		; // ********* CONTINUE HERE
	else
		ft_putendl_fd("Error", 2);
	free_memory(path, target, a, b);
	exit(status);
}
