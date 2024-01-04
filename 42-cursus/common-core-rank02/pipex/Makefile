# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 17:49:48 by rtorrent          #+#    #+#              #
#    Updated: 2024/01/04 16:09:08 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS     := -Werror -Wextra -Wall

DEBUGFLAGS := -g

RM         := rm -f

# **************************************************************************** #

# Filenames:

NAME    := pipex

HEADER  := pipex.h

SRC :=	ft_getenv.c\
		ft_strspn.c\
		link_pipeline.c\
		parse_pipeline.c\
		pipex.c

OBJ     := $(SRC:.c=.o)

DIRLIB  := libft/

NAMELB  := libft.a

HDRLIB  := libft.h

NAMEGDB := pipex-gdb

MKFILE  := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

$(NAME) $(NAMEGDB):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) fclean; fi

$(NAME) $(NAMEGDB)::
	@$(MAKE) -s -C $(DIRLIB) --no-print-directory all

$(NAME) $(NAMEGDB):: $(OBJ) $(DIRLIB)$(NAMELB)
	$(CC) $^ -o $@

clean: clean1
	@$(MAKE) -C $(DIRLIB) --no-print-directory clean

clean1:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(DIRLIB)$(NAMELB)
	$(RM) $(NAME)
	$(RM) $(NAMEGDB)

re: fclean all

debug: clean1 $(NAMEGDB)

.PHONY: all clean clean1 fclean re debug

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRLIB)$(HDRLIB)

# **************************************************************************** #

# Target-specific assignments:

debug: CFLAGS += $(DEBUGFLAGS)
