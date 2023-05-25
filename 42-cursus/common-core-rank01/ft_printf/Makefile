# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 10:39:47 by rtorrent          #+#    #+#              #
#    Updated: 2023/05/25 15:04:19 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS += -Werror -Wextra -Wall

AR     := ar rcsv
RM     := rm -f

# **************************************************************************** #

# Filenames:

NAME   := libftprintf.a

HEADER := ft_printf.h

SRC    := ft_printf.c\
	libft/ft_memcpy.c\
	libft/ft_strchr.c\
	libft/ft_strlen.c

OBJ    := $(SRC:.c=.o)

# **************************************************************************** #

# Primary targets:

$(NAME): $(OBJ)
	$(AR) $@ $?

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #

# Build prerequisites:

%.o: %.c $(HEADER) 
	$(CC) $(CFLAGS) -o $@ -c $<
