/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:11:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 01:03:17 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	end_push_swap(t_stack *sta, t_stack *stb, t_list **p_ops, int status)
{
	free(sta);
	free(stb);
	if (p_ops)
		ft_lstclear(p_ops, free);
	if (status)
		ft_putstr_fd("Error\n", 2);
	exit(status);
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
	while (ft_isdigit(*str) && !*status)
	{
		i = *str++ - '0';
		if ((sgn && n < (INT_MIN + i) / 10) || (!sgn && n > (INT_MAX - i) / 10))
			*status = OOB_ERR;
		if (sgn)
			n = 10 * n - i;
		else
			n = 10 * n + i;
	}
	if (*str && !*status)
		*status = NAN_ERR;
	return (n);
}

int	fill_stack(size_t *dst, const int *src, size_t size)
{
	const int *const	src_0 = src;
	const int *const	src_n = src + size;
	const int			*src_current;
	size_t				ordinal;

	while (size--)
	{
		src_current = src_0 + size;
		ordinal = 0;
		src = src_0;
		while (src < src_n)
		{
			if (src == src_current)
				;
			else if (*src < *src_current)
				ordinal++;
			else if (*src == *src_current)
				return (DUP_ERR);
			src++;
		}
		dst[size] = ordinal;
	}
	return (SUCCESS);
}

void	init_stacks(t_stack **p_sta, t_stack **p_stb, size_t n, char *args[])
{
	size_t			i;
	int				error_flag;
	int *const		arguments = malloc(n * sizeof(int));
	const size_t	size_struct = sizeof(t_stack) + n * sizeof(size_t);

	error_flag = SUCCESS;
	*p_sta = malloc(size_struct);
	*p_stb = malloc(size_struct);
	if (!(*p_sta && *p_stb))
		error_flag = MEM_ERR;
	i = 0;
	while (!error_flag && i < n)
		arguments[i++] = atoi2(*++args, &error_flag);
	if (!error_flag)
	{
		(*p_sta)->n = n;
		error_flag = fill_stack((*p_sta)->stack, arguments, n);
		(*p_stb)->n = 0;
	}
	free(arguments);
	if (error_flag)
		end_push_swap(*p_sta, *p_stb, NULL, error_flag);
}

int	main(int argc, char *argv[])
{
	t_list	*ops;
	t_stack	*sta;
	t_stack	*stb;

	if (argc == 1)
		exit(SUCCESS);
	ops = NULL;
	init_stacks(&sta, &stb, argc - 1, argv);
	ft_printf("Testing ...\n");
	end_push_swap(sta, stb, &ops, SUCCESS);
}
