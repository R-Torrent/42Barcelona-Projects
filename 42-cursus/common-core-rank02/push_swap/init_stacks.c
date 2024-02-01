/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stacks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:03:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 19:00:38 by rtorrent         ###   ########.fr       */
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

int	fill_stack(t_stack *sta, const int *src, unsigned int size)
{
	const int *const	src_0 = src;
	const int *const	src_n = src + size;
	unsigned int		*ordinal;

	while (size--)
	{
		ordinal = ft_calloc(1, sizeof(unsigned int));
		if (!ordinal)
			return (MEM_ERR);
		src = src_0;
		while (src < src_n)
		{
			if (*src < src_0[size])
				(*ordinal)++;
			else if (src != (src_0 + size) && *src == src_0[size])
				return (DUP_ERR);
			src++;
		}
		if (!ft_stapush(sta, ordinal))
		{
			free(ordinal);
			return (MEM_ERR);
		}
	}
	return (SUCCESS);
}

int	init_stacks(t_stack **pa, t_stack **pb, unsigned int n, char *args[])
{
	int				status;
	int *const		arguments = malloc(n * sizeof(int));
	unsigned int	i;

	status = SUCCESS;
	*pa = ft_stanew(n);
	*pb = ft_stanew(n);
	if (!(*pa && *pb))
		status = MEM_ERR;
	i = 0;
	while (!status && i < n)
		arguments[i++] = atoi2(*++args, &status);
	if (!status)
		status = fill_stack(*pa, arguments, n);
	free(arguments);
	return (status);
}
