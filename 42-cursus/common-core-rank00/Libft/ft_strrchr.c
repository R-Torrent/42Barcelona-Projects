/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 02:35:08 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/06 03:03:26 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *sc;
	const char *sc_last;

	sc_last = sc = ft_strchr(s, c);
	while (sc && *sc)
	{
		sc_last = sc;
		sc = ft_strchr(++sc, c);
	}
	return ((char *)sc_last);
}
