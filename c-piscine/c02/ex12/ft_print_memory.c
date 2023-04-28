/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:23:40 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/17 18:26:23 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>

void	print_hex(unsigned char c)
{
	unsigned char	h;
	unsigned char	hex[2];

	h = c / 16 + '0';
	if (h > '9')
		h = h - '9' - 1 + 'a';
	hex[0] = h;
	h = c % 16 + '0';
	if (h > '9')
		h = h - '9' - 1 + 'a';
	hex[1] = h;
	write(1, hex, 2);
}

void	print_first_address(unsigned char *addr, size_t size_pointer)
{
	unsigned char	*c;	

	c = (unsigned char *)&addr;
	while (size_pointer--)
		print_hex(*(c + size_pointer));
}

void	print_hexadecimal_content(unsigned char *c, unsigned int n)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (n)
		{
			print_hex(*c++);
			n--;
		}
		else
			write(1, "  ", 2);
		if (i % 2)
			write(1, " ", 1);
		i++;
	}
}

void	print_printable_content(unsigned char *c, unsigned int n)
{
	unsigned int	i;
	unsigned char	display[17];

	i = 0;
	while (i < n)
	{
		if ('\040' <= c[i] && c[i] <= '\176')
			display[i] = c[i];
		else
			display[i] = '.';
		i++;
	}
	display[i] = '\n';
	write(1, display, n + 1);
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned char	*c;
	unsigned int	n;

	c = (unsigned char *)addr;
	while (size)
	{
		print_first_address(c, sizeof(c));
		write(1, ": ", 2);
		if (size >= 16)
			n = 16;
		else
			n = size;
		print_hexadecimal_content(c, n);
		print_printable_content(c, n);
		c += n;
		size -= n;
	}
	return (addr);
}
/*
int	main()
{
	ft_print_memory("Bonjour les aminches\t\n\tc\a est fou\ttout"
			"\tce qu on peut faire avec\t\n\tprint_memory\n\n\n"
			"\tlol.lol\n ", 92);
//	ft_print_memory("Hello! :)", 0);
}
*/
