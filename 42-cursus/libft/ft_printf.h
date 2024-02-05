/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:00:28 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/05 19:18:28 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* ************************************************************************** */

# define PRINTF_FLD_SIZE 32

typedef struct s_specf
{
	long	ival;
	char	*str;
	size_t	size;
}	t_specf;

/* ************************************************************************** */

// principal routine for the 'printf' family of functions (stdio.h)

int	xx_printf(void *dst, int (*pf)(void *, const char *, size_t),
		const char *format, va_list *pap);

/* ************************************************************************** */

#endif
