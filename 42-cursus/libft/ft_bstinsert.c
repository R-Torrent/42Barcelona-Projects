/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:59:45 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/28 00:09:11 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbst.h"

static bool	insert(t_bst *bst, t_node **pnode, const void *content,
	const void *key)
{
	int	comp;

	if (!*pnode)
	{
		*pnode = malloc(sizeof(t_node));
		if (!*pnode)
			return (false);
		(*pnode)->content = (void *)content;
		(*pnode)->left = NULL;
		(*pnode)->right = NULL;
		return (true);
	}
	comp = bst->compf(key, bst->keycalc((*pnode)->content));
	if (comp < 0)
		return (insert(bst, &(*pnode)->left, content, key));
	else if (comp > 0)
		return (insert(bst, &(*pnode)->right, content, key));
	return (false);
}

bool	ft_bstinsert(t_bst *bst, const void *content)
{
	if (!bst || !content)
		return (false);
	return (insert(bst, &bst->root, content, bst->keycalc(content)));
}
