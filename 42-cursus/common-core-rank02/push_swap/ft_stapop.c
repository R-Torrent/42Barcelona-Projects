/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stapop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:23:25 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 00:49:10 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	*ft_stapop(t_stack *const sta)
{
	t_frame	*top_frame;
	void	*top_content;

	if (!ft_staisempty(sta))
	{
		top_frame = sta->top;
		top_content = top_frame->content;
		sta->size--;
		sta->top = top_frame->below;
		if (!top_frame->index)
			free(top_frame);
		return (top_content);
	}
	return (NULL);
}
