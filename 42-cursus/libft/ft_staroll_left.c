/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_staroll_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 22:55:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 20:42:07 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	ft_staroll_left(t_stack *sta)
{
	t_frame	*frame;
	void	*top_content;
	void	*content;

	if (ft_stasize(sta) > 1)
	{
		frame = sta->top;
		top_content = frame->content;
		frame = frame->below;
		while (frame)
		{
			content = frame->content;
			frame->content = top_content;
			top_content = content;
			frame = frame->below;
		}
		sta->top->content = top_content;
	}
}
