/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:03:50 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/07 11:22:22 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_size;
	char	*dst;

	s_size = ft_strlen(s) + 1;
	dst = malloc(s_size);
	if (dst)
		ft_strlcpy(dst, s, s_size);
	return (dst);
}
