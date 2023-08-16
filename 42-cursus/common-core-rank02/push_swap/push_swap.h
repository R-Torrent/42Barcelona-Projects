/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:54:19 by rtorrent          #+#    #+#             */
/*   Updated: 2023/08/16 14:20:08 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

/* ************************************************************************** */

# include <limits.h>

// external declarations from the libc (AKA 'authorized functions')
void	exit(int status);

/* ************************************************************************** */

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

typedef struct s_stack
{
	size_t	maxsize;
	size_t	top;
	size_t	stack[];
}	t_stack;

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
	RRR
};

// MORE STUFF HERE

/* ************************************************************************** */

#endif
