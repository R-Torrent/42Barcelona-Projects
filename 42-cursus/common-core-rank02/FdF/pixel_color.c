/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 02:03:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/17 03:05:15 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// integer square root
// version of Heron's method, as found in
// https://en.wikipedia.org/wiki/Integer_square_root
static unsigned int	isqrt(unsigned int num, unsigned int den)
{
	unsigned int	n = num / den; // <---- ** CONTINUE WORK HERE ***

	if (n <= 1)
		return (n);
	return (n / 2);
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
	int	color_trgb[4];
	int	i;

	if (a->color_trgb != b->color_trgb)
	{
		dist[0] = dist_chebyshev(&p->c, &a->c);
		dist[1] = dist_chebyshev(&p->c, &b->c);
		dist[2] = dist[0] + dist[1];
		color_trgb[0] = a->color_trgb;
		color_trgb[1] = b->color_trgb;
		p->color_trgb = BLACK;
		i = 3;
		while (i--)
		{
			color_trgb[2] = color_trgb[0] & BLUE;
			color_trgb[3] = color_trgb[1] & BLUE;
			p->color_trgb <<= 8;
			p->color_trgb |= isqrt(dist[0] * color_trgb[3] * color_trgb[3]
					+ dist[1] * color_trgb[2] * color_trgb[2], dist[2]);
			color_trgb[0] >>= 8;
			color_trgb[1] >>= 8;
		}
	}
	return (p->color_trgb);
}
