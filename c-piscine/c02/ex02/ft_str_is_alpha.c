/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:18:36 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/11 15:34:18 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char *str)
{
	while (*str)
	{
		if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
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
	char string2[] = "sjjeJHHKsdkjhfjH";
	char string3[] = "hd s";
	char string4[] = "69!37.3";
	printf("%s -> %d\n", string1, ft_str_is_alpha(string1));
	printf("%s -> %d\n", string2, ft_str_is_alpha(string2));
	printf("%s -> %d\n", string3, ft_str_is_alpha(string3));
	printf("%s -> %d\n", string4, ft_str_is_alpha(string4));
	return 0;
}
*/
