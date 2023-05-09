/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:32:44 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/09 13:34:13 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
		lst = lst->next;
	return (lst);
}
