/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:03:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/13 23:20:04 by rtorrent         ###   ########.fr       */
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
	return (0xff);
}

static int	simple_color(const int *dist, const t_point *a, const t_point *b)
{
	if (dist[1] > dist[0])
		return (a->color);
	return (b->color);
}

// Chebyshev distance (L_inf metric)
// https://en.wikipedia.org/wiki/Chebyshev_distance
static int	dist_chebyshev(const struct s_coord p1, const struct s_coord p2)
{
	const int	dist[2] = {ft_abs(p1.x - p2.x), ft_abs(p1.y - p2.y)};

	if (dist[1] > dist[0])
		return (dist[1]);
	return (dist[0]);
}

int	pixel_color(t_map_fdf *map, const t_point *a, t_point *p, const t_point *b)
{
	int				dist[2];
	unsigned int	k;
	int				mask;
	int				color[2];

	if (a->color != b->color)
	{
		dist[0] = dist_chebyshev(p->c1, a->c1);
		dist[1] = dist_chebyshev(p->c1, b->c1);
		if (!(map->flags & CGRAD))
			return (simple_color(dist, a, b));
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
