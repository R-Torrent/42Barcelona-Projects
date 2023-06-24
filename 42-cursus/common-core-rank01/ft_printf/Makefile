# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 10:39:47 by rtorrent          #+#    #+#              #
#    Updated: 2023/06/24 15:57:54 by rtorrent         ###   ########.fr        #
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

SRC    := ft_printf.c

OBJ    := $(SRC:.c=.o)

DIRLIB := libft/

NAMELB := libft.a

HDRLIB := libft.h

SRCLIB := ft_memcpy.c\
	ft_strlen.c\
	ft_strchr.c\
	ft_toupper.c

OBJLIB := $(addprefix $(DIRLIB),$(SRCLIB:.c=.o))

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

$(NAME):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) fclean; fi

$(NAME):: makelib

$(NAME):: $(OBJ) $(OBJLIB)
	$(AR) $@ $?

makelib:
	@$(MAKE) -C $(DIRLIB) all

clean:
	@$(MAKE) -C $(DIRLIB) clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(DIRLIB)$(NAMELB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all makelib clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRLIB)$(HDRLIB)
	$(CC) $(CFLAGS) -o $@ -c $<
