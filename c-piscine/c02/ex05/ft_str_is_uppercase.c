/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:39:35 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/11 15:39:32 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_uppercase(char *str)
{
	while (*str)
	{
		if (*str >= 'A' && *str <= 'Z')
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
	char string2[] = "DSGKJGHDNEH";
	char string3[] = "XdHs";
	char string4[] = "sx!37.3";
	printf("%s -> %d\n", string1, ft_str_is_uppercase(string1));
	printf("%s -> %d\n", string2, ft_str_is_uppercase(string2));
	printf("%s -> %d\n", string3, ft_str_is_uppercase(string3));
	printf("%s -> %d\n", string4, ft_str_is_uppercase(string4));
	return 0;
}
*/
