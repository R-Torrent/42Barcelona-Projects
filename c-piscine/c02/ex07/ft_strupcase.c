/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:50:18 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/11 13:20:33 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strupcase(char *str)
{
	char	*str0;

	str0 = str;
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str &= ~0x20;
		str++;
	}
	return (str0);
}
/*
#include <stdio.h>
int main(void)
{
	char c[] = {'h', 'E', 'l', 'L', 'o', ' ', '4', '2', '!', '\0'};
	printf("%s\n", ft_strupcase(c));
	return 0;
}
*/
