/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:21:49 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/07 21:41:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef char (*t_func1)(unsigned int, char);
typedef void (*t_func2)(unsigned int, char *);


static t_func2	aux(t_func2)
{
// *** WORK IN PROGRESS
}

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*p;

	p = ft_strdup(s);
	ft_striteri(p, 

	return (p);
}
