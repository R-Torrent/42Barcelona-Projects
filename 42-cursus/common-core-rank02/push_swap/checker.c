/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 00:03:27 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/16 01:13:07 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	main(int argc, char *argv[])
{
	t_info	info;
	t_node	*progress;
	int		status;

	if (!--argc)
		exit(SUCCESS);
	progress = malloc(info.size_node);
	if (!progress)
		status = MEM_ERR;
	else
		status = init_root(&info, (unsigned int)argc, argv);
	while (status == WORKING)
	{
		ft_memcpy(progress, info.temp_nodes0, info.size_node);
		status = run_instruction(&info, progress);
	}
	if (status == SUCCESS)
		ft_putendl_fd("OK", 1);
	else if (status == NOT_FND)
		ft_putendl_fd("KO", 1);
	else
		ft_putendl_fd("Error", 2);
	free(progress);
	free(info.temp_nodes0);
	exit(status);
}
