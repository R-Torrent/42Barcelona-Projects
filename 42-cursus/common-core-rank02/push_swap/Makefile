# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/11 21:35:28 by rtorrent          #+#    #+#              #
#    Updated: 2023/08/14 19:04:43 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS += -Werror -Wextra -Wall

RM     := rm -f

# **************************************************************************** #

# Filenames:

NAME   := push_swap

HEADER := push_swap.h

SRC    := push_swap.c

OBJ    := $(SRC:.c=.o)

DIRLIB := libft/

NAMELB := libft.a

HDRLIB := libft.h

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

$(NAME):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) fclean; fi

$(NAME)::
	@$(MAKE) -C $(DIRLIB) all

$(NAME):: $(OBJ) $(DIRLIB)$(NAMELB)

clean:
	@$(MAKE) -C $(DIRLIB) clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(DIRLIB)$(NAMELB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRLIB)$(HDRLIB)
