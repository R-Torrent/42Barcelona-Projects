/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:26:29 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/09 12:27:50 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	g_fd;

static void	f_aux(unsigned int ui, char *pc)
{
	(void)ui;
	ft_putchar_fd(*pc, g_fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	g_fd = fd;
	ft_striteri(s, f_aux);
}
