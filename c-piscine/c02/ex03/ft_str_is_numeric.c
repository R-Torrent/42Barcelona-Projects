/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:42:46 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/11 15:36:38 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_numeric(char *str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
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
	char string2[] = "23jeJHHKsdkjhfjH";
	char string3[] = "hd s";
	char string4[] = "069373";
	printf("%s -> %d\n", string1, ft_str_is_numeric(string1));
	printf("%s -> %d\n", string2, ft_str_is_numeric(string2));
	printf("%s -> %d\n", string3, ft_str_is_numeric(string3));
	printf("%s -> %d\n", string4, ft_str_is_numeric(string4));
	return 0;
}
*/
