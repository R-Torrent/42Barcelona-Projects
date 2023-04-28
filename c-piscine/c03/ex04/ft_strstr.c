/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:09:36 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/20 14:20:10 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	char	*str1;
	char	*tfn1;

	while (*str)
	{
		str1 = str;
		tfn1 = to_find;
		while (*str1 && *tfn1 && *str1 == *tfn1)
		{
			str1++;
			tfn1++;
		}
		if (!*tfn1)
			return (str);
		str++;
	}
	return ((char *)0);
}

#include <stdio.h>
int main()
{
	char *a = "I swallowed a wax glob!";
	char *b = "wa";
	char *c = "";

	printf("%s\n", ft_strstr(a, b));
	printf("%s\n", ft_strstr(b, a));
	printf("%s\n", ft_strstr(a, c));
	printf("%s\n", ft_strstr(c, a));		

	char *largestring = "Foo Bar Baz";
	char *smallstring = "Bar";
	printf("%s\n", ft_strstr(largestring, smallstring));
}

