# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 20:52:16 by rtorrent          #+#    #+#              #
#    Updated: 2024/01/30 23:31:17 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

# Use 'make CFLAGS=-g [rule(s)]' to compile with the '-g' switch, that is,
# "generate debugging information".
override CFLAGS += -Werror -Wextra -Wall

AR     := ar rcsv
RM     := rm -f
TC     := touch

# **************************************************************************** #

# Filenames:

NAME   := libft.a
LIST   := .list
BSTREE := .bintree

HEADER := libft.h
HDRLST := liblst.h
HDRBST := libbst.h

SRC    := ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_dprintf.c\
	ft_getenv.c\
	ft_getnextline_fd.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_islower.c\
	ft_isprint.c\
	ft_isspace.c\
	ft_isupper.c\
	ft_itoa.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_printf.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_sprintf.c\
	ft_strchr.c\
	ft_strcspn.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strspn.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c\
	xx_printf.c

SRCLST := ft_lstadd_back.c\
	ft_lstadd_front.c\
	ft_lstclear.c\
	ft_lstdelone.c\
	ft_lstiter.c\
	ft_lstlast.c\
	ft_lstmap.c\
	ft_lstnew.c\
	ft_lstsize.c\
	ft_lsttoarray.c

SRCBST := ft_bstclear.c\
	ft_bstdelone.c\
	ft_bstdeltree.c\
	ft_bstinsert.c\
	ft_bstnew.c\
	ft_bstsearch.c

OBJ    := $(SRC:.c=.o)
OBJLST := $(SRCLST:.c=.o)
OBJBST := $(SRCBST:.c=.o)

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME) $(LIST) $(BSTREE)

$(NAME) $(LIST) $(BSTREE):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) --no-print-directory fclean; fi

list: $(LIST)

bintree: $(BSTREE)

$(NAME):: $(OBJ)
	$(AR) $@ $?

$(LIST):: $(OBJLST)
	$(AR) $(NAME) $?
	@$(TC) $(LIST)

$(BSTREE):: $(OBJBST)
	$(AR) $(NAME) $?
	@$(TC) $(BSTREE)

clean:
	$(RM) $(OBJ) $(OBJLST) $(OBJBST)
	@$(RM) $(LIST) $(BSTREE)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all list bintree clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): $(HEADER)

$(OBJLST): $(HDRLST)

$(OBJBST): $(HDRBST)

ft_printf.o ft_getnextline_fd.o: %.o: %.h
