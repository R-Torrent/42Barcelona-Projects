/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_staswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 23:54:36 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 20:42:38 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	ft_staswap(t_stack *sta)
{
	void	*top_content;

	if (ft_stasize(sta) > 1)
	{
		top_content = sta->top->content;
		sta->top->content = sta->top->below->content;
		sta->top->below->content = top_content;
	}
}
