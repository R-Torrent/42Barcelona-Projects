# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 10:39:47 by rtorrent          #+#    #+#              #
#    Updated: 2023/05/25 20:35:00 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS += -Werror -Wextra -Wall

AR     := ar rcsv
RM     := rm -f

# **************************************************************************** #

# Filenames:

NAME   := libftprintf.a

HEADER := ft_printf.h

SRC    := ft_printf.c

OBJ    := $(SRC:.c=.o)

DIRLIB := libft/

NAMELB := libft.a

HDRLIB := libft.h

SRCLIB := ft_memcpy.c\
	ft_strlen.c\
	ft_strchr.c

OBJLIB := $(addprefix $(DIRLIB),$(SRCLIB:.c=.o))

# **************************************************************************** #

# Primary targets:

all: makelib $(NAME)

makelib:
	@$(MAKE) -C $(DIRLIB) all

$(NAME): $(OBJ) $(OBJLIB)
	$(AR) $@ $?

clean:
	@$(MAKE) -C $(DIRLIB) clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(DIRLIB)$(NAMELB)
	$(RM) $(NAME)

re: fclean all

.PHONY: all makelib clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): %.o: %.c $(HEADER) $(DIRLIB)$(HDRLIB)
	$(CC) $(CFLAGS) -o $@ -c $<
