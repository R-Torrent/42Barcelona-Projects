/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:19:37 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/06 18:30:33 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/ft_printf.h"

static void	hextoa(t_specf *const pspecf, const char c)
{
	int				numd;
	unsigned long	uval;
	const char		hex[] = "0123456789abcdef";

	numd = PRINTF_FLD_SIZE;
	if (c == 'p')
		uval = pspecf->ival;
	else
		uval = (unsigned int)pspecf->ival;
	if (!uval)
		pspecf->str[--numd] = '0';
	while (uval)
	{
		if (c == 'X')
			pspecf->str[--numd] = ft_toupper(hex[uval % 16]);
		else
			pspecf->str[--numd] = hex[uval % 16];
		uval /= 16;
	}
	pspecf->size = PRINTF_FLD_SIZE - numd;
	if (c == 'p')
		ft_memcpy(ft_memcpy(pspecf->str, "0x", 2) + 2, pspecf->str + numd,
			pspecf->size);
	else
		ft_memcpy(pspecf->str, pspecf->str + numd, pspecf->size);
}

static void	itoa(t_specf *const pspecf, const char c)
{
	int				numd;
	unsigned int	uval;
	const bool		minus = (c == 'i' || c == 'd') && pspecf->ival < 0;

	numd = PRINTF_FLD_SIZE;
	if (minus)
		uval = -pspecf->ival;
	else
		uval = pspecf->ival;
	if (!uval)
		pspecf->str[--numd] = '0';
	while (uval)
	{
		pspecf->str[--numd] = uval % 10 + '0';
		uval /= 10;
	}
	if (minus)
		pspecf->str[--numd] = '-';
	pspecf->size = PRINTF_FLD_SIZE - numd;
	ft_memcpy(pspecf->str, pspecf->str + numd, pspecf->size);
}

static char	*get_field(t_specf *const pspecf, const char c, va_list *pap)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
	{
		pspecf->ival = va_arg(*pap, int);
		if (c == 'x' || c == 'X')
			hextoa(pspecf, c);
		else
			itoa(pspecf, c);
	}
	else if (c == 'p')
	{
		pspecf->ival = (long)va_arg(*pap, void *);
		hextoa(pspecf, c);
		pspecf->size += 2;
	}
	else if (c == 'c')
		pspecf->str[pspecf->size++] = va_arg(*pap, int);
	else if (c == 's')
	{
		pspecf->str = va_arg(*pap, char *);
		if (pspecf->str)
			pspecf->size = ft_strlen(pspecf->str);
	}
	else
		pspecf->str[pspecf->size++] = c;
	return (pspecf->str);
}

static int	sift(int fd, const char **pformat, va_list *pap)
{
	const char	*p;
	char		str[PRINTF_FLD_SIZE];
	t_specf		specf;
	int			nc;
	int			nc1;

	p = *pformat;
	while (*p && *p != '%')
		p++;
	nc = write(fd, *pformat, p - *pformat);
	if (nc != -1 && *p == '%')
	{
		specf.str = str;
		specf.size = 0;
		if (get_field(&specf, *++p, pap))
			nc1 = write(fd, specf.str, specf.size);
		else
			nc1 = write(fd, "(null)", 6);
		if (nc1 == -1)
			return (-1);
		nc += nc1;
		p++;
	}
	*pformat = p;
	return (nc);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		nc;
	int		nc1;

	va_start(ap, format);
	nc = 0;
	while (*format)
	{
		nc1 = sift(fd, &format, &ap);
		if (nc1 == -1)
			return (-1);
		nc += nc1;
	}
	va_end(ap);
	return (nc);
}
