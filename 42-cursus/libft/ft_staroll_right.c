/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_staroll_right.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:25:50 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 20:42:16 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	ft_staroll_right(t_stack *sta)
{
	t_frame	*frame;
	void	*top_content;

	if (ft_stasize(sta) > 1)
	{
		frame = sta->top;
		top_content = frame->content;
		while (frame->below)
		{
			frame->content = frame->below->content;
			frame = frame->below;
		}
		frame->content = top_content;
	}
}
