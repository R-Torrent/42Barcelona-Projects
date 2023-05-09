/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:16:54 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/09 16:42:51 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

void	ft_lstclear(t_lst **plst, void (*del)(void *))
{
	t_lst	*lst;
	t_lst	*next;

	lst = *plst;
	next = lst;
	while (next)
	{
		next = lst->next;
		ft_lstdelone(lst, del);
	}
	*plst = NULL;
}
