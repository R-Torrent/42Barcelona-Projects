/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stapeek.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:17:20 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 20:41:09 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	*ft_stapeek(const t_stack *sta)
{
	if (!ft_staisempty(sta))
		return (sta->top->content);
	else
		return (NULL);
}
