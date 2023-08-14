/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:11:04 by rtorrent          #+#    #+#             */
/*   Updated: 2023/08/14 21:17:19 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	end_pshswp(t_stack *p_sta, t_stack *p_stb, t_list **p_ops, bool err)
{
	free(p_sta);
	free(p_stb);
	if (p_ops)
		ft_lstclear(p_ops, free);
	if (!err)
		exit(0);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

static void	init_stacks(t_stack *p_sta, t_stack *p_stb, int n, char *argv[])
{
	const size_t	s1 = sizeof(t_stack);
	const size_t	s2 = offsetof(t_stack, stack) + n * sizeof(int);
	size_t			s;

	(void)argv;
	if (!n)
		exit(0);
	if (s1 > s2)
		s = s1;
	else
		s = s2;
	p_sta = malloc(s);
	p_stb = malloc(s);
	if (!p_sta || !p_stb)
		end_pshswp(p_sta, p_stb, NULL, true);
	p_sta->maxsize = n;
	p_stb->maxsize = n;
}

int	main(int argc, char *argv[])
{
	t_stack	sta;
	t_stack	stb;
	t_list	*ops;

	ops = NULL;
	init_stacks(&sta, &stb, argc - 1, argv);
	ft_printf("Testing ...\n");
	end_pshswp(&sta, &stb, &ops, false);
}
