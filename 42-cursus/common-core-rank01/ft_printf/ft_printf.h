/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:00:28 by rtorrent          #+#    #+#             */
/*   Updated: 2023/08/12 14:43:17 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

/* ************************************************************************** */

# include <stdarg.h>

/* ************************************************************************** */

# define FLD_SIZE 32

typedef struct s_specf
{
	long	ival;
	char	*str;
	size_t	size;
}	t_specf;

int	ft_printf(const char *s, ...);

/* ************************************************************************** */

#endif
