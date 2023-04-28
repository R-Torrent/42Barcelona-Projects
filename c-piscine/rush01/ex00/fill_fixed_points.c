/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fixed_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:15:02 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/09 21:18:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

void	fill(int x, int y, t_direction dir, t_fixed type)
{
	int		i;

	if (type == SEE1)
		g_board[x][y] = 4;
	else if (type == SEE4)
	{
		i = 1;
		while (i < 5)
		{
			if (dir == UP)
				g_board[x][y--] = i;
			else if (dir == DW)
				g_board[x][y++] = i;
			else if (dir == LF)
				g_board[x--][y] = i;
			else
				g_board[x++][y] = i;
			i++;
		}
	}
	else if (type == SEE2n3)
	{
		if (dir == UP)
			g_board[x][--y] = 4;
		else if (dir == DW)
			g_board[x][++y] = 4;
		else if (dir == LF)
			g_board[--x][y] = 4;
		else
			g_board[++x][y] = 4;
	}
}
