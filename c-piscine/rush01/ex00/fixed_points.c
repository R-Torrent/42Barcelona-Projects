/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:29:36 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/09 21:41:19 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush-01.h"

// Finds fixed results, according to the game rules
void	forced_pos(int *set)
{
	int			i;
	t_fixed		type;
	t_factor	factor;

	i = 0;
	while (i < 16)
	{
		if (i < 4 || (i < 12 && i > 7))
			factor = UP_LF;
		else
			factor = DW_RI;
		if (set[i] == 1)
			type = SEE1;
		else if (set[i] == 4)
				type = SEE4;
		else if (set[i] == 2 && (set[i + (4 * factor)] == 3))
				type = SEE2n3;
		else
		{
			i++;
			continue ;
		}
		if (i == 0)
			fill(0, 0, DW, type);
		else if (i == 1)
			fill(1, 0, DW, type);
		else if (i == 2)
			fill(2, 0, DW, type);
		else if (i == 3)
			fill(3, 0, DW, type);
		else if (i == 4)
			fill(0, 3, UP, type);
		else if (i == 5)
			fill(1, 3, UP, type);
		else if (i == 6)
			fill(2, 3, UP, type);
		else if (i == 7)
			fill(3, 3, UP, type);
		else if (i == 8)
			fill(0, 0, RI, type);
		else if (i == 9)
			fill(0, 1, RI, type);
		else if (i == 10)
			fill(0, 2, RI, type);
		else if (i == 11)
			fill(0, 3, RI, type);
		else if (i == 12)
			fill(3, 0, LF, type);
		else if (i == 13)
			fill(3, 1, LF, type);
		else if (i == 14)
			fill(3, 2, LF, type);
		else /* i == 15 */
			fill(3, 3, LF, type);
		i++;
	}
}
