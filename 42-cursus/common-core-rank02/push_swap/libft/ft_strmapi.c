/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:21:49 by rtorrent          #+#    #+#             */
/*   Updated: 2023/07/04 19:50:36 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	(*g_f)(size_t i, char c);

static void	f_aux(size_t i, char *c)
{
	*c = g_f(i, *c);
}

char	*ft_strmapi(const char *s, char (*f)(size_t, char))
{
	char *const	p = ft_strdup(s);

	if (p)
	{
		g_f = f;
		ft_striteri(p, f_aux);
	}
	return (p);
}
