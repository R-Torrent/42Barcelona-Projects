/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 00:04:47 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/06 18:35:55 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/ft_printf.h"

static int	putfn(void *dst, const char *buf, size_t nbytes)
{
	t_specf *const	dst1 = (t_specf *)dst;
	size_t			written;

	if (nbytes < dst1->size)
		written = nbytes;
	else
		written = dst1->size - 1;
	dst1->str = (char *)ft_memcpy(dst1->str, buf, written) + written;
	dst1->size -= written;
	return ((int)nbytes);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list			ap;
	int				nc;
	t_specf *const	dst = &(t_specf){0, str, size};

	va_start(ap, format);
	nc = xx_printf(dst, &putfn, format, ap);
	if (nc >= 0)
		*dst->str = '\0';
	va_end(ap);
	return (nc);
}
