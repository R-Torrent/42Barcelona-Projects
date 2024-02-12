/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:54:19 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/12 18:34:15 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

/* ************************************************************************** */

# include <limits.h>
# include <stdint.h>

// external declarations from the libc (AKA 'authorized functions')
void	exit(int status);

/* ************************************************************************** */

// algorithm still running
# define WORKING -1
// successful completion
# define SUCCESS 0
// memory allocation error
# define MEM_ERR 1
// not a number error
# define NAN_ERR 2
// out of bounds error
# define OOB_ERR 3
// duplicate error
# define DUP_ERR 4
// solution not found
# define NOT_FND 5

// minimim path size and subsequent batch allocations
// used in: ft_getnextline_fd of the libft
# undef DEFAULT_BATCH_SZE
# define DEFAULT_BATCH_SZE 100

enum e_ops
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	ID
};

enum e_stacks
{
	A,
	B
};

typedef struct s_node
{
	struct s_node	*camefrom;
	unsigned int	moves;
	enum e_ops		camewith;
	size_t			n[2];
	unsigned int	stacks[];
}	t_node;

int		ida_star(t_node **ppath, size_t n, t_node *temp_nodes);
t_node	*pop_node(t_node **ppath, t_node *node, size_t size_node);
t_node	*push_node(t_node **ppath, t_node *node, size_t size_node, int *status);

/* ************************************************************************** */

#endif
