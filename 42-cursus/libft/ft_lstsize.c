/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:46:32 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 23:35:24 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblst.h"

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
