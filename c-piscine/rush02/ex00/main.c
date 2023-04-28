/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:36:41 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/16 23:58:52 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static void	print_dictionary_error(void)
{
	write(1, "Dict Error\n", 11);
}

int	main(int argc, char *argv[])
{
	int		result;
	int		number;
	int		dict_size;
	char	*file;
	t_entry	*dictionary;

	result = check_input(argc, argv, &number, &file);
	if (result != SUCCESS)
		return (result);
	result = dictionary_fill(file, &dictionary, &dict_size);
	if (result != SUCCESS)
	{
		print_dictionary_error();
		return (result);
	}
	result = ft_itow(number, dictionary, dict_size);
	if (result != SUCCESS)
	{
		print_dictionary_error();
		return (result);
	}
	write(1, "\n", 1);
	return (SUCCESS);
}
