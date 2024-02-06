# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 17:49:48 by rtorrent          #+#    #+#              #
#    Updated: 2024/02/06 00:35:48 by rtorrent         ###   ########.fr        #
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

NAME    := pipex

HEADER  := pipex.h

SRC :=	ft_dprintf.c\
		ft_getenv.c\
		ft_lsttoarray.c\
		ft_snprintf.c\
		ft_strspn.c\
		link_pipeline.c\
		parse_pipeline.c\
		pipex.c

OBJ     := $(SRC:.c=.o)

DIRLIB  := libft/

NAMELB  := libft.a

HDRLIB  := libft.h

DEBUG   := .debug

MKFILE  := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME)

bonus: all

debug: $(DEBUG)

$(NAME) $(DEBUG):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) -s fclean; fi

$(DEBUG)::
	@if [ -f "$@" ]; then $(RM_NT_DEBUG); else $(MAKE) -s fclean; fi

$(NAME) $(DEBUG)::
	@$(MAKE) -s -C $(DIRLIB) CFLAGS="$(CFLAGS)" all

$(NAME):: $(OBJ) $(DIRLIB)$(NAMELB)

$(DEBUG):: $(OBJ) $(DIRLIB)$(NAMELB)
	$(CC) $^ -o $(NAME)
	@$(TC) $(DEBUG)

clean:
	@$(MAKE) -C $(DIRLIB) --no-print-directory clean
	$(RM) $(OBJ)
	@$(RM) $(DEBUG)

fclean: clean
	$(RM) $(DIRLIB)$(NAMELB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus debug clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRLIB)$(HDRLIB)

# **************************************************************************** #

# Target-specific assignments:

debug: CFLAGS += $(DEBUGFLAGS)
