/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:16:42 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/19 12:29:32 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int	ft_strlen(char *str)
{
	char	*str0;

	str0 = str;
	while (*str)
		str++;
	return (str - str0);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	char			*dest0;
	unsigned int	ltot;
	bool			dst_lte_size;

	dest0 = dest;
	while (*dest && (dest - dest0) < size)
		dest++;
	dst_lte_size = !*dest;
	ltot = (unsigned int)(dest - dest0 + ft_strlen(src));
	while ((dest - dest0 + 1) < size && *src)
		*dest++ = *src++;
	if (size && dst_lte_size)
		*dest = '\0';
	return (ltot);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char *a0 = "Hello";
	char *b = " world!";
	char a[40];
	
	strcpy(a, a0);
	printf("%s : %u\n", a, ft_strlcat(a, b, 15));
	strcpy(a, a0);
	printf("%s : %zu\n", a, strlcat(a, b, 15));
	strcpy(a, a0);
	printf("%s : %u\n", a, ft_strlcat(a, b, 1));
	strcpy(a, a0);
	printf("%s : %zu\n", a, strlcat(a, b, 1));
	strcpy(a, a0);
	printf("%s : %u\n", a, ft_strlcat(a, b, 5));
	strcpy(a, a0);
	printf("%s : %zu\n", a, strlcat(a, b, 5));
	strcpy(a, a0);
	printf("%s : %u\n", a, ft_strlcat(a, b, 11));
	strcpy(a, a0);
	printf("%s : %zu\n", a, strlcat(a, b, 11));
	strcpy(a, a0);
	printf("%s : %u\n", a, ft_strlcat(a, b, 0));
	strcpy(a, a0);
	printf("%s : %zu\n", a, strlcat(a, b, 0));

	return 0;
}
*/
