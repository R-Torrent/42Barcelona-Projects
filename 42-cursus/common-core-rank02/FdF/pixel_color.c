/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:03:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/17 21:08:21 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// integer square root
// algorithm using binary search, as found in
// https://en.wikipedia.org/wiki/Integer_square_root
static unsigned int	isqrt(unsigned int num, unsigned int den)
{
	unsigned int	l;
	unsigned int	m;
	unsigned int	r;

	l = 0;
	r = num / den + 1;
	while (l != r - 1)
	{
		m = (l + r) / 2;
		if (m * m * den <= num)
		l = m;
		else
			r = m;
	}
	return (l);
}

// Chebyshev distance (L_inf metric)
// https://en.wikipedia.org/wiki/Chebyshev_distance
static int	dist_chebyshev(const struct s_coord2 *c1, const struct s_coord2 *c2)
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

	if (a->color_trgb != b->color_trgb)
	{
		dist[0] = dist_chebyshev(&p->c, &a->c);
		dist[1] = dist_chebyshev(&p->c, &b->c);
		if (dist[1] > dist[0])
			p->color_trgb = a->color_trgb;
		else
			p->color_trgb = b->color_trgb;
	}
	return (p->color_trgb);
}

// nice color gradation
unsigned int	pixel_color_grd(const t_point *a, t_point *p, const t_point *b)
{
	int	dist[3];
	int	color_trgb[2];
	int	mask;
	int	i;

	if (a->color_trgb != b->color_trgb)
	{
		dist[0] = dist_chebyshev(&a->c, &p->c);
		dist[1] = dist_chebyshev(&a->c, &b->c);
		dist[2] = dist[1] - dist[0];
		mask = RED;
		p->color_trgb = BLACK;
		i = 3;
		while (i--)
		{
			color_trgb[0] = (a->color_trgb & mask) >> i * 8;
			color_trgb[1] = (b->color_trgb & mask) >> i * 8;
			p->color_trgb |= isqrt(dist[2] * color_trgb[0] * color_trgb[0]
					+ dist[0] * color_trgb[1] * color_trgb[1], dist[1])
				<< i * 8;
			mask >>= 8;
		}
	}
	return (p->color_trgb);
}
