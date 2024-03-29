/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:16:04 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/22 22:07:51 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	**ft_lsttoarray(t_list *lst)
{
	size_t	n;
	void	**a;
	t_list	*next;

	n = ft_lstsize(lst);
	a = malloc((n + 1) * sizeof(void *));
	a[n] = NULL;
	while (n--)
	{
		next = lst->next;
		a[n] = lst->content;
		free(lst);
		lst = next;
	}
	return (a);
}
