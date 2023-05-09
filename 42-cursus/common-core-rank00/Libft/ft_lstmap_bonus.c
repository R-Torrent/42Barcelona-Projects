/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:24:23 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/09 17:23:54 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

static void	*(*g_f)(void *content);
static void	(*g_del)(void *content);

static void	f_aux(void *content)
{
	void	*new_content;

	new_content = g_f(content);
	g_del(content);
	content = new_content;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	g_f = f;
	g_del = del;
	ft_lstiter(lst, f_aux);
	return (lst);
}
