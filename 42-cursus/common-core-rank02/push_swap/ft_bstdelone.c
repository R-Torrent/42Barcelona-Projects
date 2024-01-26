/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:14:28 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 22:55:29 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbst.h"

void	ft_bstdelone(t_node *node, void (*del)(void *))
{
	del(node->content);
	free(node);
}
