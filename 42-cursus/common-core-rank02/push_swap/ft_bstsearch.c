/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstsearch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:53:15 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 23:00:24 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbst.h"

static const void	*search(t_bst *bst, const t_node *node, const void *key)
{
	int comp;

	if (!node)
		return (NULL);
	comp = bst->compf(key, bst->keycalc(node->content));
	if (comp < 0)
		return (search(bst, node->left, key));
	else if (comp > 0)
		return (search(bst, node->right, key));
	return (node->content);
}

const void  *ft_bstsearch(t_bst *bst, const void *key)
{
	if (!bst || !key)
        return (NULL);
    return (search(bst, bst->root, key));
}
