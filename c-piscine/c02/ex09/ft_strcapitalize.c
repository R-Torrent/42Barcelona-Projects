/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:22:38 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/12 21:01:16 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	char	*str0;
	int		first_letter;

	str0 = str;
	first_letter = 1;
	while (*str)
	{
		if (('a' <= *str && *str <= 'z') || ('A' <= *str && *str <= 'Z'))
		{
			if (first_letter)
			{
				first_letter = 0;
				*str &= ~0x20;
			}
			else
				*str |= 0x20;
		}
		else if ('0' <= *str && *str <= '9')
			first_letter = 0;
		else
			first_letter = 1;
		str++;
	}
	return (str0);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char c[80];
	printf("%s\n", ft_strcapitalize(strcpy(c, "sAlut, comment tu vas ? 42mots "
				"quarante-deux; cinquante+et+un")));
	return 0;
}
*/
