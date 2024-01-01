/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:18:20 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/01 19:16:02 by rtorrent         ###   ########.fr       */
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

char	**form_array(t_list *lst)
{
	size_t	n;
	char	**a;
	t_list	*next;

	n = ft_lstsize(lst);
	a = malloc(n * sizeof(char *) + 1);
	a[n] = NULL;
	while (n--)
	{
		next = lst->next;
		a[n] = lst->content;
		free(lst);
		lst = next;
	}
	return (a);
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

char	**get_tokens(const char *str)
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
	return (form_array(tokens));
}

void	parse_pipeline(t_data *const pdata, const int argc, char *const argv[])
{
	const bool	here_doc = !ft_strncmp(argv[1], "here doc", 9);
	int			i;
	char		**words;

	i = 2 + here_doc;
	while (i < argc - 1)
	{
		words = get_tokens(argv[i++]);
		ft_lstadd_front(&pdata->pipeline, ft_lstnew(malloc(sizeof(t_comm))));
		*(t_comm *)pdata->pipeline->content = (t_comm){words, NULL};
	}
	redir(pdata->pipeline, here_doc, i, argv);
}
