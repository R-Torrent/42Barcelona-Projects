/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stapeek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:17:20 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 00:48:51 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	*ft_stapeek(t_stack *const sta)
{
	if (!ft_staisempty(sta))
		return (ft_stapush(sta, ft_stapop(sta)));
	else
		return (NULL);
}
