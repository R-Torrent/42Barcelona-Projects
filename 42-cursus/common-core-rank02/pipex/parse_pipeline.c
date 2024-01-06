/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:18:20 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/06 12:29:32 by rtorrent         ###   ########.fr       */
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

void	seek_binary(t_list *const pln, char *const *paths)
{
	t_comm *const		comm = (t_comm *)pln->content;
	char				*word;
	char *const *const	paths0 = paths;

	word = *comm->words;
	if (!ft_strchr(word, '/'))
	{
		word = ft_strjoin("/", word);
		while (*paths)
		{
			comm->binary = ft_strjoin(*paths, word);
			if (!access(comm->binary, F_OK))
				break ;
			free(comm->binary);
			comm->binary = NULL;
			paths++;
		}
		free(word);
	}
	else if (!access(word, F_OK))
		comm->binary = ft_strdup(word);
	if (pln->next)
		seek_binary(pln->next, paths0);
}

size_t	get_one_token(size_t *n, char *dst, const char *src)
{
	const char *const	src0 = src;
	unsigned int		q;

	q = 0;
	while (*src && (q || (*src != ' ' && *src != '\t')))
	{
		if (*src == '\'' && !(q & ~QUOT_SQ))
			q ^= QUOT_SQ;
		else if (*src == '\"' && !(q & ~QUOT_DQ))
			q ^= QUOT_DQ;
		else
		{
			if (*src == '\\'
				&& (!q || (q & QUOT_DQ && (src[1] == '\"' || src[1] == '\\'))))
				src++;
			if (dst)
				*dst++ = *src;
			(*n)++;
		}
		src++;
	}
	if (dst)
		*dst = '\0';
	return (src - src0);
}

char	**get_tkns(const char *str)
{
	t_list	*tokens;
	size_t	n;
	char	*word;

	tokens = NULL;
	str += ft_strspn(str, " \t");
	while (*str)
	{
		n = 1;
		get_one_token(&n, NULL, str);
		word = malloc(n);
		str += get_one_token(&n, word, str);
		ft_lstadd_front(&tokens, ft_lstnew(word));
		str += ft_strspn(str, " \t");
	}
	return ((char **)ft_lsttoarray(tokens));
}

void	parse_pln(t_list **const ppln, char *const *paths, const int argc,
		char *const *argv)
{
	const bool	here_doc = !ft_strncmp(argv[1], "here doc", 9);
	int			i;

	i = 2 + here_doc;
	while (i < argc - 1)
	{
		ft_lstadd_front(ppln, ft_lstnew(malloc(sizeof(t_comm))));
		*(t_comm *)(*ppln)->content = (t_comm){NULL, get_tkns(argv[i++]), NULL};
	}
	seek_binary(*ppln, paths);
	redir(*ppln, here_doc, i, argv);
}
