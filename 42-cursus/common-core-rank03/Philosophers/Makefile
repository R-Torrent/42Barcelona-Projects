# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 18:32:36 by rtorrent          #+#    #+#              #
#    Updated: 2024/03/23 18:38:22 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS     := -Werror -Wextra -Wall

DEBUGFLAGS := -g

RM         := rm -f
TC         := touch
RM_NT_DEBUG = find . -type f -name "*.o" -newer $(DEBUG) -delete

# **************************************************************************** #

# Filenames:

NAME    := philo

HEADER  := philo.h

SRC :=	philo.c\

OBJ     := $(SRC:.c=.o)

DEBUG   := .debug

MKFILE  := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

debug: $(DEBUG)

$(NAME) $(DEBUG):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) -s fclean; fi

$(DEBUG)::
	@if [ -f "$@" ]; then $(RM_NT_DEBUG); else $(MAKE) -s fclean; fi

$(NAME):: $(OBJ)

$(DEBUG):: $(OBJ)
	$(CC) $^ -o $(NAME)
	@$(TC) $(DEBUG)

clean:
	$(RM) $(OBJ)
	@$(RM) $(DEBUG)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all  debug clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER)

# **************************************************************************** #

# Target-specific assignments:

debug: CFLAGS += $(DEBUGFLAGS)
