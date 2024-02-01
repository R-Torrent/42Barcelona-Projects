/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_staclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 23:43:15 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 20:38:51 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	ft_staclear(t_stack *sta, void (*del)(void *))
{
	while (!ft_staisempty(sta))
		del(ft_stapop(sta));
}
