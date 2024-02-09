/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stadup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:04:00 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/08 22:13:46 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

static void	stadup(t_stack *new, t_frame *frame, void *(*dup)(const void *))
{
	if (frame->below)
		stadup(new, frame->below, dup);
	ft_stapush(new, dup(frame->content));
}
	
t_stack	*ft_stadup(const t_stack *sta, void *(*dup)(const void *))
{
	t_stack	*new;

	if (sta)
	{
		new = ft_stanew(sta->capacity);
		if (new && !ft_staisempty(sta))
			stadup(new, sta->top, dup);
		return (new);
	}
	return (NULL);
}
