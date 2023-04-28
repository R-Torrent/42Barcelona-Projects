/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubert- <jaubert-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 00:31:55 by jaubert-          #+#    #+#             */
/*   Updated: 2023/04/17 00:38:37 by jaubert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

void	helper_1(int n, int *len, t_entry *dictionary, int dict_len)
{
	ft_putstr(ft_find_by_key((n / ft_exp(10, *len - 1)) % 100, dictionary, dict_len));
	if (*len - 1 != 0)
		write(1, " ", 1);
}
