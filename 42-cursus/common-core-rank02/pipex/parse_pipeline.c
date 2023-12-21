/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:18:20 by rtorrent          #+#    #+#             */
/*   Updated: 2023/12/21 13:04:14 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redir(t_list *const pln, bool hdoc, const int argc1, char *const argv[])
{
	t_redir *const	rdr[2] = {malloc(sizeof(t_redir)), malloc(sizeof(t_redir))};

	if (hdoc)
	{
		*rdr[0] = (t_redir){argv[2], RDR_HEREDOC};
		*rdr[1] = (t_redir){argv[argc1], RDR_APPOUT};
	}
	else
	{
		*rdr[0] = (t_redir){argv[1], RDR_INPUT};
		*rdr[1] = (t_redir){argv[argc1], RDR_OUTPUT};
	}
	ft_lstadd_back(&((t_comm *)ft_lstlast(pln)->content)->redir,
		ft_lstnew(rdr[0]));
	ft_lstadd_back(&((t_comm *)pln->content)->redir, ft_lstnew(rdr[1]));
}

void	parse_pipeline(t_data *const pdata, const int argc, char *const argv[])
{
	const bool	here_doc = !ft_strncmp(argv[1], "here doc", 9);
	int			i;
	char		**words;

	i = 2 + here_doc;
	while (i < argc - 1)
	{
		words = ft_split(argv[i++], ' ');
		ft_lstadd_front(&pdata->pipeline, ft_lstnew(malloc(sizeof(t_comm))));
		*(t_comm *)pdata->pipeline->content = (t_comm){words, NULL};
	}
	redir(pdata->pipeline, here_doc, i, argv);
}
