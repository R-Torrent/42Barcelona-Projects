# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/11 21:35:28 by rtorrent          #+#    #+#              #
#    Updated: 2024/02/01 01:02:01 by rtorrent         ###   ########.fr        #
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

NAME   := push_swap

HEADER := push_swap.h
HDRSTA := libsta.h

SRC    := init_stacks.c\
	push_swap.c

SRCSTA := ft_staclear.c\
	ft_staisempty.c\
	ft_stanew.c\
	ft_stapop.c\
	ft_stapush.c\
	ft_staroll_left.c\
	ft_staroll_right.c\
	ft_stasize.c\
	ft_staswap.c

OBJ    := $(SRC:.c=.o)
OBJSTA := $(SRCSTA:.c=.o)

DIRLIB := libft/
NAMELB := libft.a
HDRLIB := libft.h

DEBUG   := .debug

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

bonus:
# Work in progress!

debug: $(DEBUG)

$(NAME) $(DEBUG):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) -s fclean; fi

$(DEBUG)::
	@if [ -f "$@" ]; then $(RM_NT_DEBUG); else $(MAKE) -s fclean; fi

$(NAME) $(DEBUG)::
	@$(MAKE) -s -C $(DIRLIB) CFLAGS="$(CFLAGS)" all

$(NAME):: $(OBJ) $(OBJSTA) $(DIRLIB)$(NAMELB)

$(DEBUG):: $(OBJ) $(OBJSTA) $(DIRLIB)$(NAMELB)
	$(CC) $^ -o $(NAME)
	@$(TC) $(DEBUG)

clean:
	@$(MAKE) -C $(DIRLIB) --no-print-directory clean
	$(RM) $(OBJ) $(OBJSTA)
	@$(RM) $(DEBUG)

fclean: clean
	$(RM) $(DIRLIB)$(NAMELB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus debug clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRLIB)$(HDRLIB)

$(OBJSTA): %.o: %.c $(HDRSTA)

# **************************************************************************** #

# Target-specific assignments:

debug: CFLAGS += $(DEBUGFLAGS)
