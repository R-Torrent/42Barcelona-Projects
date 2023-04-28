/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:20:41 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/12 19:25:09 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_non_printable(char *str)
{
	unsigned char	c;
	unsigned char	h;
	unsigned char	hex[3];

	hex[0] = '\\';
	while (*str)
	{
		c = (unsigned char)(*str);
		if ('\040' <= c && c <= '\176')
			write(1, &c, 1);
		else
		{
			h = c / 16 + '0';
			if (h > '9')
				h = h - '9' - 1 + 'a';
			hex[1] = h;
			h = c % 16 + '0';
			if (h > '9')
				h = h - '9' - 1 + 'a';
			hex[2] = h;
			write(1, hex, 3);
		}
		str++;
	}
}
/*
int main()
{
	ft_putstr_non_printable("Coucou\ntu vas bien ?");
}
*/
