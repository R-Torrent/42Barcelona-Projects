/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 23:17:12 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/05 19:22:16 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/ft_printf.h"

static int	putfn(void *dst, const char *buf, size_t nbytes)
{
	*(char **)dst = ft_memcpy(*(char **)dst, buf, nbytes) + nbytes;
	return ((int)nbytes);
}

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list	ap;
	int		nc;

	va_start(ap, format);
	nc = xx_printf(&str, &putfn, format, &ap);
	if (nc >= 0)
		*str = '\0';
	va_end(ap);
	return (nc);
}
