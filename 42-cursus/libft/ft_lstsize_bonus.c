/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:46:32 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/18 14:11:30 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	g_size;

static void	f_aux(void *content)
{
	(void)content;
	g_size++;
}

size_t	ft_lstsize(t_list *lst)
{
	g_size = 0;
	ft_lstiter(lst, f_aux);
	return (g_size);
}
