# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 14:32:05 by rtorrent          #+#    #+#              #
#    Updated: 2024/07/09 00:44:12 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS     := -Werror -Wextra -Wall -pthread
LDFLAGS    := -pthread
DEBUGFLAGS := -g

RM         := rm -f
TC         := touch
RM_NT_DEBUG = find . -type f -name "*.o" -newer $(DEBUG) -delete

# **************************************************************************** #

# Filenames:

NAME    := philo_bonus

HEADER  := philo_bonus.h

SRC     := load_simulation.c\
	philo_bonus.c\
	run_controller.c\
	run_philosopher.c\
	timekeeping.c

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
	$(CC) $(LDFLAGS) $^ -o $(NAME)
	@$(TC) $(DEBUG)

clean:
	$(RM) $(OBJ)
	@$(RM) $(DEBUG)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all debug clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER)

# **************************************************************************** #

# Target-specific assignments:

debug: CFLAGS += $(DEBUGFLAGS)
