/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:48:47 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/11 15:40:11 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Printable characters as determined by the 'isprint' function of
 * standard library 'ctype.h' */
int	ft_str_is_printable(char *str)
{
	while (*str)
	{
		if (*str >= '\040' && *str <= '\176')
			str++;
		else
			return (0);
	}
	return (1);
}
/*
#include <stdio.h>
int main()
{
	char string1[] = "";
	char string2[] = "23je.#!JR; @Ksdr]{k|~f/H";
	char string3[] = "hd\ts";
	char string4[] = "069373\n";
	printf("%s -> %d\n", string1, ft_str_is_printable(string1));
	printf("%s -> %d\n", string2, ft_str_is_printable(string2));
	printf("%s -> %d\n", string3, ft_str_is_printable(string3));
	printf("%s -> %d\n", string4, ft_str_is_printable(string4));
	return 0;
}
*/
