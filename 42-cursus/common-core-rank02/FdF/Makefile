# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 21:04:05 by rtorrent          #+#    #+#              #
#    Updated: 2024/03/25 02:42:09 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS0    := -Werror -Wextra -Wall
CFLAGS      = $(CFLAGS0) -I$(DIRFT) -I$(DIRMLX)
LDFLAGS     = -L$(DIRFT) -L$(DIRMLX)
LDLIBS     := -lft -lmlx -lXext -lX11
OPTIMIZE   := -O3
DEBUGFLAGS := -g -Og

VPATH       = $(DIRFT):$(DIRMLX)

RM         := rm -rf

TC         := touch

RM_NT_DEBUG = find . -type f -name "*.o" -newer $(DEBUG) -delete

EXTRACT_MLX = tar -xvf $(TARMLX)

# **************************************************************************** #

# Filenames and folders:

NAME   := fdf

HEADER := fdf.h

SRC    := fdf.c\
	fdf_utils.c\
	ft_abs.c\
	ft_isxdigit.c\
	ft_strtok.c\
	ft_strtok_r.c\
	mappings.c\
	pixel_color.c\
	plot_wires.c\
	read_data.c

OBJ    := $(SRC:.c=.o)

DIRFT  := libft/
LIBFT  := libft.a
HDRFT  := libft.h

DIRMLX := minilibx-linux/
LIBMLX := libmlx.a
HDRMLX := mlx.h
TARMLX := resources/minilibx-linux.tgz

DEBUG  := .debug

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

debug: $(DEBUG)

$(NAME) $(DEBUG):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) -s fclean; fi

$(DEBUG)::
	@if [ -f "$@" ]; then $(RM_NT_DEBUG); else $(MAKE) -s fclean0; fi

$(NAME) $(DEBUG)::
	@echo "Working on your request..."
	@$(MAKE) -s -C $(DIRFT) CFLAGS="$(CFLAGS0)" all
	@if [ ! -d "$(DIRMLX)" ]; then $(EXTRACT_MLX); fi
	@$(MAKE) -s -C $(DIRMLX) all

$(NAME) $(DEBUG):: $(OBJ) $(LDLIBS)
	$(CC) $(LDFLAGS) $^ -o $(NAME)

$(DEBUG):: $(OBJ) $(LDLIBS)
	@$(TC) $(DEBUG)

$(LDLIBS):

clean:
	@$(MAKE) -C $(DIRFT) --no-print-directory clean
	@if [ -d "$(DIRMLX)" ]; then $(MAKE) -C $(DIRMLX) --no-print-directory clean; fi
	$(RM) $(OBJ)
	@$(RM) $(DEBUG)

fclean0: clean
	$(RM) $(DIRFT)$(LIBFT)
	$(RM) $(NAME)

fclean: fclean0
	$(RM) $(DIRMLX)

re: fclean all

.PHONY: all debug clean fclean0 fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRFT)$(HDRFT) $(DIRMLX)$(HDRMLX)

# **************************************************************************** #

# Target-specific assignments:

$(NAME): CFLAGS0 += $(OPTIMIZE)

debug: CFLAGS0 += $(DEBUGFLAGS)
