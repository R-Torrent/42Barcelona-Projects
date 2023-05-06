/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:16:42 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/06 18:54:03 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const char	*dst0;
	size_t		len_dst;
	size_t		len_src;

	dst0 = dst;
	while (size > 1 && *dst)
		dst++, size--;
	len_dst = dst - dst0;
	len_src = ft_strlcpy(dst, src, size);
	return (len_dst + len_src);
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
