# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/11 21:35:28 by rtorrent          #+#    #+#              #
#    Updated: 2024/02/17 21:27:10 by rtorrent         ###   ########.fr        #
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
BONUS  := checker

HEADER := push_swap.h
SRC    := ida_star.c\
	init_root.c\
	operate_stacks.c\
	push_swap.c
OBJ    := $(SRC:.c=.o)

HDRBON := push_swap_bonus.h
SRCBON := checker_bonus.c\
	init_root.c\
	operate_stacks.c
OBJBON := $(SRCBON:.c=.o)

DIRLIB := libft/
NAMELB := libft.a
HDRLIB := libft.h

DEBUG  := .debug

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

bonus: $(BONUS)

debug: $(DEBUG)

$(NAME) $(BONUS) $(DEBUG):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) -s fclean; fi

$(DEBUG)::
	@if [ -f "$@" ]; then $(RM_NT_DEBUG); else $(MAKE) -s fclean; fi

$(NAME) $(BONUS) $(DEBUG)::
	@$(MAKE) -s -C $(DIRLIB) CFLAGS="$(CFLAGS)" all

$(NAME):: $(OBJ) $(DIRLIB)$(NAMELB)

$(BONUS):: $(OBJBON) $(DIRLIB)$(NAMELB)
	$(CC) $^ -o $(BONUS)

$(DEBUG):: $(OBJ) $(OBJBON) $(DIRLIB)$(NAMELB)
	$(CC) $^ -o $(NAME)
	$(CC) $^ -o $(BONUS)
	@$(TC) $(DEBUG)

clean:
	@$(MAKE) -C $(DIRLIB) --no-print-directory clean
	$(RM) $(OBJ) $(OBJBON)
	@$(RM) $(DEBUG)

fclean: clean
	$(RM) $(DIRLIB)$(NAMELB)
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus debug clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRLIB)$(HDRLIB)

$(OBJBON): %.o: %.c $(HDRBON) $(DIRLIB)$(HDRLIB)

# **************************************************************************** #

# Target-specific assignments:

debug: CFLAGS += $(DEBUGFLAGS)
