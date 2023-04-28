/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:48 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/19 13:41:01 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
/*
#include <stdio.h>
int main()
{
	char *s1, * s2, s[] = {'h', 'e', 'l', 'l', 'o', '\0'};

	s1 = "hello", s2 = s;
	printf("%d: \"%s\" \"%s\"\n", ft_strcmp(s1, s2), s1, s2);
	s1 = "hell";
	printf("%d: \"%s\" \"%s\"\n", ft_strcmp(s1, s2), s1, s2);
	s1 = s, s2 = "";
	printf("%d: \"%s\" \"%s\"\n", ft_strcmp(s1, s2), s1, s2);
	s1 = "arbol", s2 = "arboreo";
	printf("%d: \"%s\" \"%s\"\n", ft_strcmp(s1, s2), s1, s2);
}
*/
