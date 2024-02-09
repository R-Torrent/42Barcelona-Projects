/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:54:19 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/09 01:57:12 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "libsta.h"

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

typedef struct s_step
{
	t_stack			*a;
	t_stack			*b;
	enum e_ops		camewith;
}	t_step;

void	ida_star(t_stack *path, const t_stack *target);
int		init_stacks(t_stack **pa, t_stack **pb, unsigned int n, char *args[]);

/* ************************************************************************** */

#endif
