/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:44:57 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/05 19:18:47 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	putfn(void *dst, const char *buf, size_t nbytes)
{
	(void)dst;
	return ((int)write(1, buf, nbytes));
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			nc;

	va_start(ap, format);
	nc = xx_printf(NULL, &putfn, format, &ap);
	va_end(ap);
	return (nc);
}
