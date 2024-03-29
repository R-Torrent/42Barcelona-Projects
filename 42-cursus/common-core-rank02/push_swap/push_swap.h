/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:54:19 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/20 20:15:26 by rtorrent         ###   ########.fr       */
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
// solution not found
# define NOT_FND 1
// memory allocation error
# define MEM_ERR 2
// not a number error
# define NAN_ERR 3
// out of bounds error
# define OOB_ERR 4
// duplicate error
# define DUP_ERR 5

// minimim path size and subsequent batch allocations
// used in: ft_getnextline_fd of the libft
# undef DEFAULT_BATCH_SZE
# define DEFAULT_BATCH_SZE 100

// maximum allowable moves before forced break -> NOT_FND error
// (only applicable to the IDA* algorithm) (should be < UINT_MAX)
# define LIMIT 15000

// maximum size of the problem for an exact solution (IDA*);
// falling back on an aproximate method thereafter :(
# define MAX_EXACT 9

// codes for all the instructions + initial identity (ID)
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

// stack 'a' (A) and stack 'b' (B)
enum e_stacks
{
	A,
	B
};

// turning directions of the stacks in aprox. algorithm - (DIR)ect and (REV)erse
enum e_rot
{
	DIR_DIR,
	DIR_REV,
	REV_DIR,
	REV_REV
};

// nodes stored in the 'path' stack of the solution
typedef struct s_node
{
	struct s_node	*camefrom;
	unsigned int	moves;
	enum e_ops		camewith;
	size_t			n[2];
	size_t			stacks[];
}	t_node;

// useful information and working place bounced around the program
typedef struct s_info
{
	size_t	n_args;
	size_t	size_node;
	t_node	*temp0;
	t_node	*temp1;
}	t_info;

// [aprox solution] candidates for pushing into the 'b' stack
typedef struct s_cand
{
	size_t		idxa;
	size_t		rots_t;
	size_t		rots_1;
	size_t		rots_2;
	enum e_ops	op_1;
	enum e_ops	op_2;
}	t_cand;

void	aprox(t_node **ppath, t_info *pinfo, int *pstatus);
void	ida_star(t_node **ppath, t_info *pinfo, int *pstatus);
int		init_root(t_info *pinfo, unsigned int n, char *args[]);
bool	is_goal(t_node *node, t_info *pinfo, int *pstatus);
char	*op_string(enum e_ops op);
t_info	*op_stacks(const t_node *node, enum e_ops op, t_info *pinfo);
void	pop_node(t_node **ppath);
void	push_node(t_node **ppath, t_info *pinfo, int *pstatus);

/* ************************************************************************** */

#endif
