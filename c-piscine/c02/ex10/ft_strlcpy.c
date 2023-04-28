/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:47:12 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/18 14:03:23 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	char	*str0;

	str0 = str;
	while (*str)
		str++;
	return (str - str0);
}

unsigned int	ft_strlcpy(char *dst, char *src, unsigned int size)
{
	char	*src0;

	src0 = src;
	if (!size)
		return (ft_strlen(src));
	while ((src - src0) < size - 1 && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (ft_strlen(src0));
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char a[] = "Hello!";
	char c[20];
	char d[20];

	printf("%s : %d\n", c, ft_strlcpy(c, a, 15));
	printf("%s : %lu\n", d, strlcpy(d, a, 15));

	printf("%s : %d\n", c, ft_strlcpy(c, a, 1));
	printf("%s : %lu\n", d, strlcpy(d, a, 1));

	printf("%s : %d\n", c, ft_strlcpy(c, a, 5));
	printf("%s : %lu\n", d, strlcpy(d, a, 5));

	printf("%s : %d\n", c, ft_strlcpy(c, a, 0));
	printf("%s : %lu\n", d, strlcpy(d, a, 0));

	printf("%s : %d\n", c, ft_strlcpy(c, "", 3));
	printf("%s : %lu\n", d, strlcpy(d, "", 3));
	return 0;
}
*/
