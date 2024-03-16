/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:29:20 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/16 21:32:58 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	cross_product(int vax, int vay, int vbx, int vby)
{
	return (vax * vby - vay * vbx);
}

int	atoi2(const char *str, int *status)
{
	int	n;
	int	i;
	int	sgn;

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
			*status = 1;
		if (sgn)
			n = 10 * n - i;
		else
			n = 10 * n + i;
	}
	if (*str)
		*status = 1;
	return (n);
}

unsigned int	atou2(const char *str, int *status)
{
	unsigned int	n;
	unsigned int	u;
	unsigned int	b;
	const char		hex[] = "0123456789abcdef";

	while (ft_isspace(*str))
		str++;
	b = 10;
	if (!ft_strncmp(str, "0x", 2) || !ft_strncmp(str, "0X", 2))
	{
		b = 16;
		str += 2;
	}
	n = 0;
	while ((b == 10 && ft_isdigit(*str)) || (b == 16 && ft_isxdigit(*str)))
	{
		u = ft_strchr(hex, ft_tolower(*str++)) - hex;
		if (n > (UINT_MAX - u) / b)
			*status = 1;
		n = b * n + u;
	}
	if (*str)
		*status = 1;
	return (n);
}
