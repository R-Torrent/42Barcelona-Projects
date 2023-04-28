/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:14:34 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/11 15:38:19 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
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
	char string2[] = "sajesdkjhfj";
	char string3[] = "hdHs";
	char string4[] = "sx!37.3";
	printf("%s -> %d\n", string1, ft_str_is_lowercase(string1));
	printf("%s -> %d\n", string2, ft_str_is_lowercase(string2));
	printf("%s -> %d\n", string3, ft_str_is_lowercase(string3));
	printf("%s -> %d\n", string4, ft_str_is_lowercase(string4));
	return 0;
}
*/
