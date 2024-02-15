/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:54:19 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/15 16:48:36 by rtorrent         ###   ########.fr       */
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

// maximum allowable moves before forced break -> NOT_FND error
// (should be < UINT_MAX)
# define LIMIT 15000

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
	size_t			stacks[];
}	t_node;

typedef struct s_info
{
	size_t	n_args;
	size_t	size_node;
	t_node	*temp_nodes0;
	t_node	*temp_nodes1;
}	t_info;

int		ida_star(t_node **ppath, t_info *pinfo);
t_node	*operate_stacks(t_node *path, enum e_ops op, t_info *pinfo);
void	pop_node(t_node **ppath);
void	push_node(t_node **ppath, t_info *pinfo, enum e_ops op, int *status);

/* ************************************************************************** */

#endif
