/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:45:40 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/09 21:46:01 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

int g_board[4][4] = {0};
int g_mirror[4][4]  = {0};

void	print_board()
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < 4)
	{
		printf("%d", g_board[x][y]);
		printf("%c", ' ');
		x++;
		if (x > 3)
		{
			printf("%c", '\n');
			
			x = 0;
			y++;
		}
	}
	printf("%c", '\n');
}

int view_check(int x, int y, int dir, int n)
{
	int		count;
	int		highest;

	count = 1;
	highest = g_board[x][y];
	while (x <= 3 && x >= 0 && y <= 3 && y >= 0)
	{
		if (g_board[x][y] > highest)
		{
			highest = g_board[x][y];
			count++;
		}
		if (dir == 0)
			y--;
		else if (dir == 1)
			y++;
		else if (dir == 2)
			x--;
		else
			x++;
	}
	if (count != n)
		return (1);
	else
		return (0);
}

int	check_i(int *set)
{
	int		i;
	int		flag;

	i = 0;
	while (i < 16)
	{
		if (i == 0)
			flag = (view_check(0, 0, 1, set[i]));
		else if (i == 1)
			flag = (view_check(1, 0, 1, set[i]));
		else if (i == 2)
			flag = (view_check(2, 0, 1, set[i]));
		else if (i == 3)
			flag = (view_check(3, 0, 1, set[i]));
		else if (i == 4)
			flag = (view_check(0, 3, 0, set[i]));
		else if (i == 5)
			flag = (view_check(1, 3, 0, set[i]));
		else if (i == 6)
			flag = (view_check(2, 3, 0, set[i]));
		else if (i == 7)
			flag = (view_check(3, 3, 0, set[i]));
		else if (i == 8)
			flag = (view_check(0, 0, 3, set[i]));
		else if (i == 9)
			flag = (view_check(0, 1, 3, set[i]));
		else if (i == 10)
			flag = (view_check(0, 2, 3, set[i]));
		else if (i == 11)
			flag = (view_check(0, 3, 3, set[i]));
		else if (i == 12)
			flag = (view_check(3, 0, 2, set[i]));
		else if (i == 13)
			flag = (view_check(3, 1, 2, set[i]));
		else if (i == 14)
			flag = (view_check(3, 2, 2, set[i]));
		else if (i == 15)
			flag = (view_check(3, 3, 2, set[i]));
		if (flag == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_rep_col_row(int x, int y, int n)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (g_board[i][y] == n && i != x)
			return (1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (g_board[x][i] == n && i != y)
			return (1);
		i++;
	}
	return (0);
}

int	set_num(int rec)
{
	int		x;
	int		y;
	int		n;
	int		dir;
	int		retro;

	dir = 1;
	retro = 0;
	n = 1;
	x = 0;
	y = 0;
	if (rec == 1)
	{
		x = 3;
		y = 3;
		while (y >= 0)
		{
			if (g_mirror[x][y] != 1)
				break;
			else
				x--;
			if (x < 0)
			{
				y--;
				x = 3;
			}
		}
	}
	while (y < 4)
	{
		if (y < 0)
			return (1);
		if (g_mirror[x][y] == 0)
		{
			if (rec == 1)
			{
				n = g_board[x][y];
			}
			else
			{
				if (retro == 1)
				{
					n = g_board[x][y] + 1;
					retro = 0;
				}
				dir = 1;
				g_board[x][y] = n;
			}
			
			if (check_rep_col_row(x, y, n) == 0 && rec == 0)
			{	
				x++;
				n = 1;
			}
			else
			{
				if (rec == 1)
					rec = 0;
				n++;
				while (n > 4 && retro == 0)
				{
					g_board[x][y] = 0;
					x--;
					dir = -1;
					retro = 1;
					
					if (x < 0)
					{
						y--; 
						x = 3;
					}
				}
			}
		}
		else
			x = x + dir;
		if (x > 3)
		{
			x = 0;
			y++;
		}
		else if (x < 0)
		{
			x = 3;
			y--;
		}
	}
	return (0);
}	

void	mirrorMatrix()
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < 4)
	{
		if (x < 4)
		{
			if (g_board[x][y] != 0)
				g_mirror[x][y] = 1;
			x++;
		}
		else
		{
			y++;
			x = 0;
		}
	}
}

int	main(int count, char** str)
{
	int		e;
	int		set[16];

	if ((e = error_check(count, str[1], set)))
		return (e);
	forced_pos(set);
	mirrorMatrix();
	set_num(0);
	while (check_i(set) == 1)
	{
		if (set_num(1) == 1)
		{
			print_error();
			return (SOLNOTF);
		}
	}
	print_board();
	return (SUCCESS);
}
