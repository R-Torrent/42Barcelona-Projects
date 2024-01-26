/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:16:48 by rtorrent          #+#    #+#             */
/*   Updated: 2024/01/26 23:18:18 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBST_H
# define LIBBST_H

// implementation of the Binary Search Tree (BST) data structure

/* ************************************************************************** */

# include <stdbool.h>
# include <stddef.h>

// external declarations from the libc (AKA 'authorized functions')
void		free(void *ptr);
void		*malloc(size_t size);

/* ************************************************************************** */

typedef struct s_node
{
	void			*content;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef const void	*t_keycalc(const void *content);

typedef int			t_compf(const void *key1, const void *key2);

typedef struct s_bst
{
	t_node		*root;
	t_keycalc	*keycalc;
	t_compf		*compf;
}	t_bst;

void		ft_bstclear(t_bst *bst, void (*del)(void *));
void		t_bstdelone(t_node *node, void (*del)(void *));
void		ft_bstdeltree(t_node *node, void (*del)(void *));
bool		ft_bstinsert(t_bst *bst, const void *content);
t_bst		*ft_bstnew(t_keycalc *keycalc, t_compf *compf);
const void	*ft_bstsearch(t_bst *bst, const void *key);

/* ************************************************************************** */

#endif
