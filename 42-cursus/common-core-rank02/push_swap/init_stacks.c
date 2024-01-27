/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:03:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/27 21:02:20 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	init_stacks(t_stack **p_sta, t_stack **p_stb, size_t n, char *args[])
{
	int				status;
	const size_t	size_struct = sizeof(t_stack) + n * sizeof(size_t);
	int *const		arguments = malloc(n * sizeof(int));
	size_t			i;

	status = SUCCESS;
	*p_sta = malloc(size_struct);
	*p_stb = malloc(size_struct);
	if (!(*p_sta && *p_stb))
		status = MEM_ERR;
	i = 0;
	while (!status && i < n)
		arguments[i++] = atoi2(*++args, &status);
	if (!status)
	{
		(*p_sta)->n = n;
		status = fill_stack((*p_sta)->stack, arguments, n);
		(*p_stb)->n = 0;
	}
	free(arguments);
	return (status);
}
