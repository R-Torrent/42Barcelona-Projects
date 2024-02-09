/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_staiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:46:12 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/08 21:45:09 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

static void	staiter(t_frame	*frame, void (*f)(void *))
{
	if (frame->below)
		staiter(frame->below, f);
	f(frame->content);
}

void	ft_staiter(t_stack *sta, void (*f)(void *))
{
	if (!ft_staisempty(sta))
		staiter(sta->top, f);
}
