/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:48:00 by rtorrent          #+#    #+#             */
/*   Updated: 2024/03/06 14:04:05 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	atoi2(const char *str, int *status)
{
	int	n;
	int	i;
	int	sgn;

	while (ft_isspace(*str))
		str++;
	sgn = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	n = 0;
	while (ft_isdigit(*str))
	{
		i = *str++ - '0';
		if ((sgn && n < (INT_MIN + i) / 10) || (!sgn && n > (INT_MAX - i) / 10))
			*status = 1;
		if (sgn)
			n = 10 * n - i;
		else
			n = 10 * n + i;
	}
	if (*str)
		*status = 1;
	return (n);
}

unsigned int	atou2(const char *str, int *status)
{
	unsigned int	n;
	unsigned int	u;
	unsigned int	b;
	const char		hex[] = "0123456789abcdef";

	while (ft_isspace(*str))
		str++;
	b = 10;
	if (!ft_strncmp(str, "0x", 2) || !ft_strncmp(str, "0X", 2))
	{
		b = 16;
		str += 2;
	}
	n = 0;
	while ((b == 10 && ft_isdigit(*str)) || (b == 16 && ft_isxdigit(*str)))
	{
		u = ft_strchr(hex, ft_tolower(*str++)) - hex;
		if (n > (UINT_MAX - u) / b)
			*status = 1;
		n = b * n + u;
	}
	if (*str)
		*status = 1;
	return (n);
}

int	resolve_data(t_point *dst, int row, int col, char *token)
{
	int		stat1;
	int		stat2;
	char	*color_str;

	stat1 = 0;
	stat2 = 0;
	dst->x0 = row;
	dst->y0 = col;
	dst->z0 = atoi2(ft_strtok(token, ","), &stat1);
	color_str = ft_strtok(NULL, "");
	if (color_str)
		dst->color = atou2(color_str, &stat2);
	else
		dst->color = WHITE;
	return (stat1 || stat2);
}

size_t	get_row(t_point **pdst, char *const line, size_t *rows)
{
	size_t	cols;
	char	*token;
	char	*line1;

	cols = 0;
	if (line)
	{
		token = ft_strtok_r(line, " \n", &line1);
		while (token)
		{
			if (pdst && resolve_data((*pdst)++, *rows, cols, token))
				return (SIZE_MAX);
			++cols;
			token = ft_strtok_r(NULL, " \n", &line1);
		}
		++*rows;
		free(line);
	}
	return (cols);
}

int	det_dims(t_map_fdf **pmap_fdf, const char *file_fdf)
{
	const int	fd_fdf = open(file_fdf, O_RDONLY);
	size_t		rows;
	size_t		cols;
	size_t		cols1;

	*pmap_fdf = NULL;
	if (fd_fdf == -1)
		return (1);
	rows = 0;
	cols = get_row(NULL, ft_getnextline_fd(fd_fdf), &rows);
	while (cols)
	{
		cols1 = get_row(NULL, ft_getnextline_fd(fd_fdf), &rows);
		if (cols1 != cols)
			break ;
	}
	*pmap_fdf = malloc(sizeof(t_map_fdf) + rows * cols * sizeof(t_point));
	if (close(fd_fdf) || (cols && cols1) || !*pmap_fdf)
		return (1);
	(*pmap_fdf)->rows = rows;
	(*pmap_fdf)->cols = cols;
	return (0);
}

int	read_data(t_map_fdf **pmap_fdf, const char *file_fdf)
{
	const int	fd_fdf = open(file_fdf, O_RDONLY);
	size_t		row;
	t_point		*new_pt;

	if (fd_fdf == -1)
		return (1);
	row = 0;
	if (!det_dims(pmap_fdf, file_fdf))
	{
		new_pt = (*pmap_fdf)->points;
		while (row < (*pmap_fdf)->rows)
			if (get_row(&new_pt, ft_getnextline_fd(fd_fdf), &row) == SIZE_MAX)
				break ;
	}
	if (close(fd_fdf) || !*pmap_fdf || row != (*pmap_fdf)->rows)
		return (1);
	return (0);
}
