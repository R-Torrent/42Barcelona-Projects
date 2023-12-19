/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:38:15 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/19 12:00:39 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_getenv(const char *name)
{
	extern char	**environ;
	const int	n = ft_strlen(name);
	int			i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], name, n) && environ[i][n] == '=')
			return (environ[i] + n + 1);
		i++;
	}
	return (NULL);
}
