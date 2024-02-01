/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stanew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 00:00:54 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 00:48:40 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsta.h"

t_stack	*ft_stanew(unsigned int capacity)
{
	t_stack *const	sta = malloc(sizeof(t_stack));

	if (sta)
		*sta = (t_stack){0, capacity, NULL};
	return (sta);
}
