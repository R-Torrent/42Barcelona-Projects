/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:46:32 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/09 16:44:30 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

static int	g_size;

static void	f_aux(void *content)
{
	g_size++;
}

int	ft_lstsize(t_list *lst)
{
	g_size = 0;
	ft_lstiter(lst, f_aux);
	return (g_size);
}
