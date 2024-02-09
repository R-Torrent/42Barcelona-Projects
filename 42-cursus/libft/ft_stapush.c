/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stapush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:27:26 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 20:57:35 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

void	*ft_stapush(t_stack *sta, void *content)
{
	unsigned int	index;
	t_frame			*new_frame;

	if (sta && (!sta->capacity || sta->size < sta->capacity))
	{
		if (!ft_staisempty(sta))
			index = (sta->top->index + 1) % DEFAULT_BATCH_SZE;
		else
			index = 0;
		if (index)
			new_frame = sta->top + 1;
		else
			new_frame = malloc(DEFAULT_BATCH_SZE * sizeof(struct s_frame));
		if (!new_frame)
			return (NULL);
		*new_frame = (struct s_frame){index, content, sta->top};
		sta->size++;
		sta->top = new_frame;
		return (content);
	}
	else
		return (NULL);
}
