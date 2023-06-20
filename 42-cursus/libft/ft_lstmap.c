/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:24:23 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/20 15:25:48 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new1;
	void	*newc;

	new = NULL;
	while (lst)
	{
		newc = f(lst->content);
		new1 = ft_lstnew(newc);
		if (!new1)
		{
			del(newc);
			ft_lstclear(&new, del);
			break ;
		}
		ft_lstadd_back(&new, new1);
		lst = lst->next;
	}
	return (new);
}
