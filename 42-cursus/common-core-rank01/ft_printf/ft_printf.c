/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:52:33 by rtorrent          #+#    #+#             */
/*   Updated: 2023/06/13 13:10:37 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FLD_SIZE 32

typedef struct s_specf
{
	long	ival;
	int		base;
	char	*str;
	size_t	size;
}	t_specf;

static void	itoa(t_specf *const pspecf, const char c)
{
	int				numd;
	unsigned long	uval;
	const char		g_lower[] = "0123456789abcdef";
	const char		g_upper[] = "0123456789ABCDEF";
	const bool		minus = (c == 'i' || c == 'd') && pspecf->ival < 0;

	numd = FLD_SIZE;
	if (minus)
		uval = -pspecf->ival;
	else
		uval = pspecf->ival;
	if (!uval && numd > 0)
		pspecf->str[--numd] = '0';
	while (uval && numd > 0)
	{
		if (c == 'X')
			pspecf->str[--numd] = g_upper[uval % pspecf->base];
		else
			pspecf->str[--numd] = g_lower[uval % pspecf->base];
		uval /= pspecf->base;
	}
	if (minus && numd > 0)
		pspecf->str[--numd] = '-';
	pspecf->size = FLD_SIZE - numd;
	ft_memcpy(pspecf->str, &pspecf->str[numd], pspecf->size);
}

static void	get_field(t_specf *const pspecf, const char c, va_list *pap)
{
	pspecf->size = 0u;
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == 'p')
	{
		if (c == 'x' || c == 'X' || c == 'p')
			pspecf->base = 16;
		else
			pspecf->base = 10;
		if (c == 'p')
			pspecf->ival = (long)va_arg(*pap, void *);
		else
			pspecf->ival = va_arg(*pap, int);
		itoa(pspecf, c);
	}
	else if (c == 'c')
		pspecf->str[pspecf->size++] = va_arg(*pap, int);
	else if (c == 's')
	{
		pspecf->str = va_arg(*pap, char *);
		pspecf->size = ft_strlen(pspecf->str);
	}
	else
		pspecf->str[pspecf->size++] = c;
}

static int	sift(const char **pformat, va_list *pap)
{
	const char	*p;
	char		str[FLD_SIZE];
	t_specf		specf;
	int			nc;
	int			nc1;

	p = *pformat;
	while (*p && *p != '%')
		++p;
	nc = write(1, *pformat, p - *pformat);
	if (nc != -1 && *p == '%')
	{
		specf.str = str;
		get_field(&specf, *++p, pap);
		nc1 = write(1, specf.str, specf.size);
		if (nc1 == -1)
			return (-1);
		nc += nc1;
		p++;
	}
	*pformat = p;
	return (nc);
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			nc;
	int			nc1;

	va_start(ap, format);
	nc = 0;
	while (*format)
	{
		nc1 = sift(&format, &ap);
		if (nc1 == -1)
			return (-1);
		nc += nc1;
	}
	va_end(ap);
	return (nc);
}
