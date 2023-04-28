/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 17:46:28 by rtorrent          #+#    #+#             */
/*   Updated: 2023/04/09 21:28:15 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#define SUCCESS 0 // SucWNcessful execution
#define SOLNOTF 1 // Solution not found
#define ILLARGC 2 // Incorrect number of arguments
#define ILLVSTR 3 // Illegal visibility string

typedef enum { FALSE, TRUE }			t_bool;
typedef enum { UP_LF = 1, DW_RI = -1 }	t_factor;
typedef enum { UP, DW, LF, RI }			t_direction;
typedef enum { SEE1, SEE4, SEE2n3 }		t_fixed;

int		error_check(int argc, char *argument, int *set);
void	print_error(void);
void	forced_pos(int *set);
void	fill(int x, int y, t_direction dir, t_fixed type);
void	mirror_matrix();

extern int g_board[4][4];
extern int g_mirror[4][4];
