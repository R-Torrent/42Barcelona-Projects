/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 21:37:08 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 22:48:50 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbst.h"

void	ft_bstclear(t_bst *bst, void (*del)(void *))
{
	if (bst)
	{
		ft_bstdeltree(bst->root, del);
		bst->root = NULL;
	}
}
