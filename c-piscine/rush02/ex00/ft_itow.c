/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubert- <jaubert-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 22:12:35 by jaubert-          #+#    #+#             */
/*   Updated: 2023/04/17 00:40:34 by jaubert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

bool	ft_is_zero(unsigned int n, int len);
bool	ft_is_3_zero(unsigned int n, int len);
void	ft_print_thousand(int len, char *value, unsigned int n);
void	ft_print_hundred(int len, int key, t_entry *dictionary, int dict_len);

int	ft_itow(unsigned int n, t_entry *dictionary, int dict_len)
{
	int		len;
	int		key;
	int		digit;
	bool	empty;
	char	*value;

	empty = true;
	len = ft_intlen(n);	
	if (n == 0)
		ft_putstr(ft_find_by_key(0, dictionary, dict_len));
	while (--len >= 0 && !ft_is_zero(n, len))
	{
		key = ft_exp(10, len);
		digit = (n / ft_exp(10, len)) % 10;
		value = ft_find_by_key(key, dictionary, dict_len);
		if (len % 3 == 1 && digit != 0)
		{
			if (digit == 1)
				helper_1(n, &len, dictionary, dict_len);
			else 
			{
				ft_putstr(ft_find_by_key(digit * 10, dictionary, dict_len));
				if ((n / ft_exp(10, len - 1)) % 10 != 0)
					write(1, " ", 1);
			}
		}
		else
		{
			if (digit != 0 && ((n / ft_exp(10, len + 1)) % 10 != 1
					|| len + 1 % 3 != 1))
				ft_putstr(ft_find_by_key(digit, dictionary, dict_len));
			if (len != 0 && digit != 0)
				write(1, " ", 1);
			ft_print_thousand(len, value, n);
			if (digit != 0)
				ft_print_hundred(len, key, dictionary, dict_len);
		}
		empty = digit == 0;
	}
	return (SUCCESS);
}

void	ft_print_thousand(int len, char *value, unsigned int n)
{
	if (len % 3 == 0 && !ft_is_3_zero(n, len) && len != 0)
	{
		ft_putstr(value);
		if (len != 0 && !ft_is_zero(n, len - 1))
			write(1, " ", 1);
	}
}

void	ft_print_hundred(int len, int key, t_entry *dictionary, int dict_len)
{
	if (len % 3 == 2)
	{
		key = key / ft_exp(10, len - (len % 3));
		ft_putstr(ft_find_by_key(key, dictionary, dict_len));
		if (len != 0)
			write(1, " ", 1);
	}
}

bool	ft_is_3_zero(unsigned int n, int len)
{
	int	result;

	result = ((n / (ft_exp(10, len))) % 10)
			+ ((n / (ft_exp(10, len + 1))) % 10)
			+ ((n / (ft_exp(10, len + 2))) % 10);
	if (result > 0)
		return (false);
	return (true);
}

bool	ft_is_zero(unsigned int n, int len)
{
	int	result;

	if (n == 0)
		return (true);

	result = 0;
	while (len >= 0)
	{
		if ((result += (n / (ft_exp(10, len))) % 10) != 0)
			return (false);
		len--;
	}
	return (true);
}

