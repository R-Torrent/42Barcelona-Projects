/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:14:12 by rtorrent          #+#    #+#             */
/*   Updated: 2023/05/16 15:57:44 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// BOGUS condition added to pass Francinette

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	const size_t	needle_len = ft_strlen(needle);

	if (!needle_len)
		return ((char *)haystack);
	while (*haystack && n-- >= needle_len)
	{
		if (!ft_strncmp(haystack, needle, needle_len))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
