/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:53:21 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/10 16:24:27 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	char	*dst0;

	dst0 = dest;
	while (*src && (dest - dst0) < n)
		*dest++ = *src++;
	while ((dest - dst0) < n)
		*dest++ = '\0';
	return (dst0);
}
/*
#include <unistd.h>
int main()
{
	char string1[] = "Hello world!";
	char string2[10];
	
	ft_strncpy(string2, string1, 4);
	write(1, string2, 10);
	return 0;
}
*/
