/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 00:04:47 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/06 00:55:18 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/ft_printf.h"

static int	putfn(void *dstv, const char *buf, size_t nbytes)
{
	struct s_snprintf_dst *const	dst = (struct s_snprintf_dst *)dstv;
	size_t							written;

	if (nbytes < *dst->psize)
		written = nbytes;
	else
		written = *dst->psize - 1;
	*dst->pstr = ft_memcpy(*dst->pstr, buf, written) + written;
	*dst->psize -= written;
	return ((int)nbytes);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	ap;
	int		nc;

	va_start(ap, format);
	nc = xx_printf(&(struct s_snprintf_dst){&str, &size}, &putfn, format, &ap);
	if (nc >= 0)
		*str = '\0';
	va_end(ap);
	return (nc);
}
