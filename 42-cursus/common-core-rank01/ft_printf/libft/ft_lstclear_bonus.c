/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:16:54 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/29 23:14:26 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **plst, void (*del)(void *))
{
	t_list	*nxt;

	while (*plst)
	{
		nxt = (*plst)->next;
		ft_lstdelone(*plst, del);
		*plst = nxt;
	}
}
