/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:57:42 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/13 19:07:25 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	char	*dst0;

	dst0 = dest;
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dst0);
}
/*
#include <stdio.h>
int main()
{
	char c[20] = { 'H', 'e', 'l', 'l', 'o', ' ', '\0' };
	printf("%s\n", ft_strcat(c, "world!"));
	return 0;
}
*/
