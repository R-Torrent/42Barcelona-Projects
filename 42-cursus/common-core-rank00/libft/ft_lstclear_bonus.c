/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:16:54 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/12 16:20:50 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **plst, void (*del)(void *))
{
	t_list	*lst;
	t_list	*next;

	lst = *plst;
	next = lst;
	while (next)
	{
		next = lst->next;
		ft_lstdelone(lst, del);
	}
	*plst = NULL;
}
