/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:43:41 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/13 18:12:46 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	if (!n)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && --n)
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
	unsigned int n;

	s1 = "hello", s2 = s, n = 5;
	printf("%d <-- \"%s\" \"%s\" n: %d\n", ft_strncmp(s1, s2, n), s1, s2, n);
	s1 = "hell", n = 3;
	printf("%d <-- \"%s\" \"%s\" n: %d\n", ft_strncmp(s1, s2, n), s1, s2, n);
	s1 = s, s2 = "", n = 20;
	printf("%d <-- \"%s\" \"%s\" n: %d\n", ft_strncmp(s1, s2, n), s1, s2, n);
	s1 = "arbol", s2 = "arboreo", n = 5;
	printf("%d <-- \"%s\" \"%s\" n: %d\n", ft_strncmp(s1, s2, n), s1, s2, n);
	s1 = "arbol", s2 = "arboreo", n = 4;
	printf("%d <-- \"%s\" \"%s\" n: %d\n", ft_strncmp(s1, s2, n), s1, s2, n);
	s1 = "pino", s2 = "roble", n = 0;
	printf("%d <-- \"%s\" \"%s\" n: %d\n", ft_strncmp(s1, s2, n), s1, s2, n);
}
*/
