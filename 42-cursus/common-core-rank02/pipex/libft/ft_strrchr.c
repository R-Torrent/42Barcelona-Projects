/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:35:08 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/10 11:09:45 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*s_last;

	s_last = NULL;
	s = ft_strchr(s, c);
	if (s && !*s)
		return ((char *)s);
	while (s)
	{
		s_last = s;
		s = ft_strchr(++s, c);
	}
	return ((char *)s_last);
}
