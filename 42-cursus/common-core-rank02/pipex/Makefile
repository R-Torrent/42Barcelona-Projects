# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/09 17:49:48 by rtorrent          #+#    #+#              #
#    Updated: 2023/12/12 19:25:42 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS += -Werror -Wextra -Wall

RM     := rm -f

# **************************************************************************** #

# Filenames:

NAME   := pipex

HEADER := pipex.h

SRC    := pipex.c

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
	@$(MAKE) -s -C $(DIRLIB) --no-print-directory all

$(NAME):: $(OBJ) $(DIRLIB)$(NAMELB)

clean:
	@$(MAKE) -C $(DIRLIB) --no-print-directory clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(DIRLIB)$(NAMELB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRLIB)$(HDRLIB)
