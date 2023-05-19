# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 10:39:47 by rtorrent          #+#    #+#              #
#    Updated: 2023/05/19 13:45:40 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS += -Werror -Wextra -Wall

AR     := ar rcv
RM     := rm -f

# **************************************************************************** #

# Filenames:

NAME   := libftprintf.a

HEADER := libftprintf.h

SRC    := ft_printf.c\
	libft/ft_memcpy.c\
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

%.o: $(HEADER) %.c
	$(CC) $(CFLAGS) -o $@ -c $<
