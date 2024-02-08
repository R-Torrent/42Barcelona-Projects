/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_staduptop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 23:56:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/08 18:00:59 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	*ft_staduptop(t_stack *sta, void *(*dup)(const void *))
{
	if (!ft_staisempty(sta))
		return (ft_stapush(sta, dup(ft_stapeek(sta))));
	return (NULL);
}
