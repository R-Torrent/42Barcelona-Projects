/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_staswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:54:36 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 01:10:04 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	ft_staswap(t_stack *const sta)
{
	void	*top_content;

	if (ft_stasize(sta) > 1)
	{
		top_content = sta->content;
		sta->content = sta->below->content;
		sta->below->content = top_content;
	}
}
