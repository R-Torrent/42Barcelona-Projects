# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 21:04:05 by rtorrent          #+#    #+#              #
#    Updated: 2024/03/03 15:52:31 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS0    := -Werror -Wextra -Wall
CFLAGS      = $(CFLAGS0) -I$(DIRFT) -I$(INCLD)
LDFLAGS     = -L$(DIRFT) -L$(LIB)
LDLIBS     := -lft -lmlx -lmlx_Linux
DEBUGFLAGS := -g

RM         := rm -f

TC         := touch

RM_NT_DEBUG = find . -type f -name "*.o" -newer $(DEBUG) -delete

# **************************************************************************** #

# Filenames and folders:

NAME   := fdf

HEADER := fdf.h

SRC    := fdf.c\
	ft_isxdigit.c\
	ft_strtok.c\
	ft_strtok_r.c\
	read_data.c

OBJ    := $(SRC:.c=.o)

DIRFT  := libft/
LIBFT  := libft.a
HDRFT  := libft.h

LIB    := /usr/local/lib/
LIBMLX := libmlx.a
INCLD  := /usr/local/include/
HDRMLX := mlx.h

DEBUG  := .debug

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

debug: $(DEBUG)

$(NAME) $(DEBUG):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) -s fclean; fi

$(DEBUG)::
	@if [ -f "$@" ]; then $(RM_NT_DEBUG); else $(MAKE) -s fclean; fi

$(NAME) $(DEBUG)::
	@$(MAKE) -s -C $(DIRFT) CFLAGS="$(CFLAGS0)" all

$(NAME):: $(OBJ)

$(DEBUG):: $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $(NAME)
	@$(TC) $(DEBUG)

clean:
	@$(MAKE) -C $(DIRFT) --no-print-directory clean
	$(RM) $(OBJ)
	@$(RM) $(DEBUG)

fclean: clean
	$(RM) $(DIRFT)$(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all debug clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRFT)$(HDRFT) $(INCLD)$(HDRMLX)

# **************************************************************************** #

# Target-specific assignments:

debug: CFLAGS0 += $(DEBUGFLAGS)
