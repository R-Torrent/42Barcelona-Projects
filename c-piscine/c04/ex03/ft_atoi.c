/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:03:47 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/20 21:54:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (c);
	if (c == '\f' || c == '\r' || c == ' ')
		return (c);
	return (0);
}

int	ft_isnumeric(int c)
{
	if ('0' <= c && c <= '9')
		return (c);
	return (0);
}

int	advance_n_determine_parity(char **str)
{
	int	p;

	p = 0;
	while (**str == '-' || **str == '+')
	{
		if (**str == '-')
			p = !p;
		(*str)++;
	}
	return (p);
}

int	ft_atoi(char *str)
{
	int	parity;
	int	n;

	while (ft_isspace(*str))
		str++;
	parity = advance_n_determine_parity(&str);
	n = 0;
	while (ft_isnumeric(*str))
	{
		n = n * 10 + *str - '0';
		str++;
	}
	if (parity)
		return (-n);
	return (n);
}
