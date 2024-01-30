/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstdeltree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:28:33 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 22:55:51 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbst.h"

void	ft_bstdeltree(t_node *node, void (*del)(void *))
{
	if (node)
	{
		ft_bstdeltree(node->left, del);
		ft_bstdeltree(node->right, del);
		ft_bstdelone(node, del);
	}
}
