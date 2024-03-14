/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:03:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/14 14:28:27 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// integer square root
// version of Heron's method, as found in
// https://en.wikipedia.org/wiki/Integer_square_root
static unsigned int	isqrt(unsigned int num)
{
	if (num <= 1)
		return (num);
	return (num / 2);
}

// Chebyshev distance (L_inf metric)
// https://en.wikipedia.org/wiki/Chebyshev_distance
static int	dist_chebyshev(const struct s_coord *c1, const struct s_coord *c2)
{
	const int	dist[2] = {ft_abs(c1->x - c2->x), ft_abs(c1->y - c2->y)};

	if (dist[1] > dist[0])
		return (dist[1]);
	return (dist[0]);
}

// simple color scheme (default)
unsigned int	pixel_color_smp(const t_point *a, t_point *p, const t_point *b)
{
	int	dist[2];

	if (a->color != b->color)
	{
		dist[0] = dist_chebyshev(&p->c, &a->c);
		dist[1] = dist_chebyshev(&p->c, &b->c);
		if (dist[1] > dist[0])
			p->color = a->color;
		else
			p->color = b->color;
	}
	return (p->color);
}

// nice color gradation
unsigned int	pixel_color_grd(const t_point *a, t_point *p, const t_point *b)
{
	int				dist[2];
	unsigned int	k;
	int				mask;
	int				color[2];

	if (a->color != b->color)
	{
		dist[0] = dist_chebyshev(&p->c, &a->c);
		dist[1] = dist_chebyshev(&p->c, &b->c);
		k = isqrt(dist[0] + dist[1]);
		p->color = 0;
		mask = RED;
		while (mask)
		{
			color[0] = a->color & mask;
			color[1] = b->color & mask;
			p->color <<= 8;
			p->color |= isqrt(dist[0] * color[0] * color[0]
					+ dist[1] * color[1] * color[1]) / k;
			mask >>= 8;
		}
	}
	return (p->color);
}
