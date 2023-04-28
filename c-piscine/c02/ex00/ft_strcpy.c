/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:07:48 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/10 16:02:41 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpy(char *dest, char *src)
{
	char	*dst0;

	dst0 = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dst0);
}
/*
#include <unistd.h>
int main()
{
	char string1[] = "Hello!";
	char string2[10];
	
	ft_strcpy(string2, string1);
	write(1, string2, 6);
	return 0;
}
*/
