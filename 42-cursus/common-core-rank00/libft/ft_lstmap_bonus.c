/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:24:23 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/13 01:46:59 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new1;

	while (lst)
	{
		new1 = ft_lstnew(f(lst->content));
		if (!new1)
		{
			ft_lstclear(&new, del);
			break;
		}
		ft_lstadd_back(&new, new1);
		lst = lst->next;
	}
	return (new);
}
