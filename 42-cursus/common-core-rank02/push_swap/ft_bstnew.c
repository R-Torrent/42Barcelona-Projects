/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:03:31 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 22:47:53 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libbst.h"

static const void	*defaultkey(const void *content)
{
	return (content);
}

t_bst   *ft_bstnew(t_keycalc *keycalc, t_compf *compf)
{
	t_bst	*new;

	if (compf == NULL)
		return (NULL);
	new = malloc(sizeof(t_bst));
	if (new)
	{
		new->root = NULL;
		if (keycalc)
			new->keycalc = keycalc;
		else
			new->keycalc = defaultkey;
		new->compf = compf;
	}
	return (new);
}
