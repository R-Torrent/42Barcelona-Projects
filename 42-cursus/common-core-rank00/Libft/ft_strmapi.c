/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:21:49 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/09 08:25:13 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	(*g_f)(unsigned int, char);

static void	f_aux(unsigned int ui, char *c)
{
	*c = g_f(ui, *c);
}

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*p;

	p = ft_strdup(s);
	if (p)
	{
		g_f = f;
		ft_striteri(p, f_aux);
	}
	return (p);
}
