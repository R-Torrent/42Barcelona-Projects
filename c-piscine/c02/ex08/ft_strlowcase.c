/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:04:31 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/11 13:19:31 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	char	*str0;

	str0 = str;
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str |= 0x20;
		str++;
	}
	return (str0);
}
/*
#include <stdio.h>
int main(void)
{
	char c[] = {'h', 'E', 'l', 'L', 'o', ' ', '4', '2', '!', '\0'};
	printf("%s\n", ft_strlowcase(c));
	return 0;
}
*/
