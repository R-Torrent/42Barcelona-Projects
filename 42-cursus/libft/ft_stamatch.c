/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stamatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:08:29 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 22:10:37 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

bool	ft_stamatch(const t_stack *sta1, const t_stack *sta2,
	int (*compar)(const void *, const void *))
{
	t_frame	*frame1;
	t_frame	*frame2;

	if (ft_staisempty(sta1) || ft_stasize(sta1) != ft_stasize(sta2))
		return (false);
	frame1 = sta1->top;
	frame2 = sta2->top;
	while (frame1 && frame2)
	{
		if (compar(frame1->content, frame2->content))
			return (false);
		frame1 = frame1->below;
		frame2 = frame2->below;
	}
	if (frame1 || frame2)
		return (false);
	return (true);
}
