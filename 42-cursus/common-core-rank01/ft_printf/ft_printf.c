/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:52:33 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/19 13:54:24 by rtorrent         ###   ########.fr       */
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

static void	itoa(t_spcf *const pspcf, const char c)
{
	size_t		nd;
	bool		minus;
	const char	lower[] = "0123456789abcdef";
	const char	upper[] = "0123456789ABCDEF";

	nd = FLD_SIZE;
	minus = pspcf->ival < 0;
	if (minus)
		pspcf->ival = -pspcf->ival;
	if (!pspcf->ival)
		pspcf->str[--nd] = '0';
	while (pspcf->ival && --nd)
	{
		if (c == 'X')
			pspcf->str[nd] = upper[pspcf->ival % pspcf->base];
		else
			pspcf->str[nd] = lower[pspcf->ival % pspcf->base];
		pspcf->ival /= pspcf->base;
	}
	if (minus)
		pspcf->str[--nd] = '-';
	pspcf->size = FLD_SIZE - nd;
	ft_memcpy(pspcf->str, &pspcf->str[nd], pspcf->size);
}

static void	get_fld(t_spcf *const pspcf, const char c, va_list *pap)
{
	pspcf->size = 0;
	if (c == 'c')
		pspcf->str[pspcf->size++] = va_arg(*pap, int);
	else if (c == 's')
	{
		pspcf->str = va_arg(*pap, char *);
		pspcf->size = ft_strlen(pspcf->str);
	}
	else if (c == '%')
		pspcf->str[pspcf->size++] = '%';
	else if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
	{
		if (c == 'x' || c == 'X')
			pspcf->base = 16;
		else
			pspcf->base = 10;
		if (c == 'u' || c == 'x' || c == 'X')
			pspcf->ival = (unsigned int)va_arg(*pap, int);
		else
			pspcf->ival = va_arg(*pap, int);
		itoa(pspcf, c);
	}
	else
		pspcf->str[pspcf->size++] = c;
}

static int	sift(const char **pp, va_list *pap)
{
	const char	*p;
	char		str[FLD_SIZE];
	t_spcf		spcf;
	int			nc;
	int			nc1;

	p = *pp;
	while (*p && *p != '%')
		p++;
	spcf.str = str;
	nc = write(1, *pp, p - *pp);
	if (nc == -1)
		return (-1);
	if (*p++)
	{
		get_fld(&spcf, *p, pap);
		nc1 = write(1, spcf.str, spcf.size);
		if (nc1 == -1)
			return (-1);
		nc += nc1;
	}
	*pp = ++p;
	return (nc);
}

int	ft_printf(const char *format, ...)
{
	const char	*p;
	va_list		ap;
	int			nc;
	int			nc1;

	p = format;
	va_start(ap, format);
	nc = 0;
	while (*p)
	{
		nc1 = sift(&p, &ap);
		if (nc1 == -1)
			return (-1);
		nc += nc1;
	}
	va_end(ap);
	return (nc);
}
