/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:42:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 23:35:11 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblst.h"

t_list	*ft_lstnew(void *content)
{
	t_list *const	p = malloc(sizeof (t_list));

	if (p)
	{
		p->content = content;
		p->next = NULL;
	}
	return (p);
}
