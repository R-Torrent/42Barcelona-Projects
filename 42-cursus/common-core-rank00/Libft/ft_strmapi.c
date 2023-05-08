/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:21:49 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/08 19:43:05 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	(*f_mapi)(unsigned int, char);

static void	f_iteri(unsigned int ui, char *c)
{
	*c = f_mapi(ui, *c);
}

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*p;

	p = ft_strdup(s);
	if (p)
	{
		f_mapi = f;
		ft_striteri(p, f_iteri);
	}
	return (p);
}
