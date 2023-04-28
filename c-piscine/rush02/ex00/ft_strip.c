/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubert- <jaubert-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:43:54 by jaubert-          #+#    #+#             */
/*   Updated: 2023/04/16 23:52:23 by jaubert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

char	*ft_strip(char *str)
{
	int		i;
	int		len;
	bool	flag;

	i = 0;
	len = 0;
	flag = false;
	while (str[i])
	{
		if (flag)
		{
			if (str[i] != ' ' || (str[i] == ' ' && str[i + 1] != ' '
					&& str[i + 1] != '\0' && len != 0))
			{
				str[len] = str[i];
				len++;
			}
		}
		if (str[i] == ':')
			flag = true;
		i++;
	}
	if (str[len])
		str[len] = '\0';
	return (str);
}
