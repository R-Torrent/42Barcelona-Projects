/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 01:38:15 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/16 03:28:17 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

char	*ft_getenv(const char *name)
{
	extern char	**environ;
	char *const	name_eq = ft_strjoin(name, "=");
	const int	n = ft_strlen(name_eq);
	int			i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], name_eq, n))
		{
			free(name_eq);
			return (environ[i] + n);
		}
		i++;
	}
	free(name_eq);
	return (NULL);
}
