/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:39:05 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/13 21:07:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char	*dst0;
	char	*dst1;

	dst0 = dest;
	while (*dest)
		dest++;
	dst1 = dest;
	while (*src && (dest - dst1) < nb)
		*dest++ = *src++;
	*dest = '\0';
	return (dst0);
}
/*
#include <stdio.h>
int main()
{
	char c[30] = { 'H', 'e', 'l', 'l', 'o', ' ', '\0' };
	printf("%s\n", ft_strncat(c, "ABCD", 0));
	printf("%s\n", ft_strncat(c, "world!", 50));
	printf("%s\n", ft_strncat(c, " *#QRT", 3));
	printf("%s\n", ft_strncat(c, "", 12));
	return 0;
}
*/
