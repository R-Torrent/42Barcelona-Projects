/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaorozco <jaorozco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:33:56 by jaorozco          #+#    #+#             */
/*   Updated: 2023/04/17 00:38:35 by jaubert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH02_H
# define RUSH02_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdbool.h>

# define SUCCESS			0
# define ARGC_ERROR			1
# define FILE_ERROR			2
# define MMRY_ERROR			3
# define DICT_ERROR			4

# define BUF_SIZE			256

typedef struct s_entry
{
	unsigned int	key;
	char			*value;
}	t_entry;

typedef struct s_array_int
{
	int	*array;
	int	length;
}	t_array_int;

typedef struct s_array_pchar
{
	char	**array;
	int		length;
}	t_array_pchar;

int		ft_atou(char *str);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
int		ft_itow(unsigned int n, t_entry *dictionary, int dict_len);
int		ft_intlen(unsigned int n);
int		ft_exp(int base, int exp);
void	ft_putstr(char *str);
char	*ft_strcpy(char *dest, char *src);
char	*ft_find_by_key(int key, t_entry *dictionary, int dict_len);
char	*ft_strip(char *str);
int		dictionary_entry_sizes(char *file, t_array_int *p_nchars_table);
int		dictionary_entries(char *file, t_array_int nchars_table, char **text,
			t_array_pchar *p_strs_table);
int		dictionary_init(char *file, char **text, t_array_pchar *index);
int		dictionary_fill(char *file, t_entry **dictionary, int *dict_size);
int		check_input(int argc, char *argv[], int *number, char **file);
void	helper_1(int n, int *len, t_entry *dictionary, int dict_len);

#endif
