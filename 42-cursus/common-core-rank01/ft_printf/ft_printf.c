/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:52:33 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/20 19:41:12 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#define FLD_SIZE 32

typedef struct s_spcf
{
	long	ival;
	int		base;
	char	*str;
	size_t	size;
}	t_spcf;
	
static char	g_lower[] = "0123456789abcdef";
static char	g_upper[] = "0123456789ABCDEF";

static void	itoa(t_spcf *const pspcf, const char c)
{
	int				nd;
	unsigned long	uval;
	const bool		minus = (c == 'i' || c == 'd') && pspcf->ival < 0;

	nd = FLD_SIZE;
	if (minus)
		uval = -pspcf->ival;
	else
		uval = pspcf->ival;
	if (!uval)
		pspcf->str[--nd] = '0';
	while (uval && --nd >= 0)
	{
		if (c == 'X')
			pspcf->str[nd] = g_upper[uval % pspcf->base];
		else
			pspcf->str[nd] = g_lower[uval % pspcf->base];
		uval /= pspcf->base;
	}
	if (minus && --nd >= 0)
		pspcf->str[nd] = '-';
	if (nd < 0)
		nd = 0;
	pspcf->size = FLD_SIZE - nd;
	ft_memcpy(pspcf->str, &pspcf->str[nd], pspcf->size);
}

static void	get_field(t_spcf *const pspcf, const char c, va_list *pap)
{
	pspcf->size = 0;
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == 'p')
	{
		if (c == 'x' || c == 'X' || c == 'p')
			pspcf->base = 16;
		else
			pspcf->base = 10;
		if (c == 'p')
			pspcf->ival = (long)va_arg(*pap, void *);
		else
			pspcf->ival = va_arg(*pap, int);
		itoa(pspcf, c);
	}
	else if (c == 'c')
		pspcf->str[pspcf->size++] = va_arg(*pap, int);
	else if (c == 's')
	{
		pspcf->str = va_arg(*pap, char *);
		pspcf->size = ft_strlen(pspcf->str);
	}
	else
		pspcf->str[pspcf->size++] = c;
}

static int	sift(const char **pformat, va_list *pap)
{
	const char	*p;
	char		str[FLD_SIZE];
	t_spcf		spcf;
	int			nc;
	int			nc1;

	p = *pformat;
	while (*p && *p != '%')
		++p;
	nc = write(1, *pformat, p - *pformat);
	if (nc == -1)
		return (-1);
	if (*p)
	{
		spcf.str = str;
		get_field(&spcf, *++p, pap);
		nc1 = write(1, spcf.str, spcf.size);
		if (nc1 == -1)
			return (-1);
		nc += nc1;
	}
	*pformat = ++p;
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
