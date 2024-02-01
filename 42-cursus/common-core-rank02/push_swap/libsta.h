/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsta.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:35:33 by rtorrent          #+#    #+#             */
/*   Updated: 2024/02/01 01:03:45 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSTA_H
# define LIBSTA_H

// implementation of the Stack data structure

/* ************************************************************************** */

# include <stdbool.h>
# include <stddef.h>

// external declarations from the libc (AKA 'authorized functions')
void			free(void *ptr);
void			*malloc(size_t size);

/* ************************************************************************** */

// minimim stack size and subsequent batch allocations
# ifndef DEFAULT_BATCH_SZE
#  define DEFAULT_BATCH_SZE 25
# endif

/* ************************************************************************** */

typedef struct s_stack
{
	unsigned int	size;
	unsigned int	capacity;
	struct s_frame	*top;
}	t_stack;

typedef struct s_frame
{
	unsigned int	index;
	void			*content;
	struct s_frame	*below;
}	t_frame;

void			ft_staclear(t_stack *const sta, void (*del)(void *));
void			*ft_stadup(t_stack *const sta, void (*dup)(void *));
bool			ft_staisempty(t_stack *const sta);
t_stack			*ft_stanew(unsigned int capacity);
void			*ft_stapeek(t_stack *const sta);
void			*ft_stapop(t_stack *const sta);
void			*ft_stapush(t_stack *const sta, const void *content);
void			ft_staroll_left(t_stack *const sta);
void			ft_staroll_right(t_stack *const sta);
unsigned int	ft_stasize(t_stack *const sta);
void			ft_staswap(t_stack *const sta);

/* ************************************************************************** */

#endif
