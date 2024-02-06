/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:14:41 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/06 18:35:33 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/ft_printf.h"

static int	putfn(void *dst, const char *buf, size_t nbytes)
{
	return ((int)write(*(int *)dst, buf, nbytes));
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		nc;

	va_start(ap, format);
	nc = xx_printf(&fd, putfn, format, ap);
	va_end(ap);
	return (nc);
}
