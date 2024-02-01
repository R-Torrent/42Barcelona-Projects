/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stadup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 23:56:38 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 00:48:17 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	*ft_stadup(t_stack *const sta, void (*dup)(void *))
{
	if (!ft_staisempty(sta))
		return (ft_stapush(sta, dup(ft_stapeek(sta))));
	return (NULL);
}
