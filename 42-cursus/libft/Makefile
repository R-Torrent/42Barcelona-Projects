# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 20:52:16 by rtorrent          #+#    #+#              #
#    Updated: 2024/02/26 22:28:41 by rtorrent         ###   ########.fr        #
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
STACK  := .stack

HEADER := libft.h
HDRPRI := ft_printf.h
HDRLST := liblst.h
HDRBST := libbst.h
HDRSTA := libsta.h

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
	ft_isxdigit.c\
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
	ft_snprintf.c\
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
	ft_strtok.c\
	ft_strtok_r.c\
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

SRCSTA := ft_staclear.c\
	ft_stadup.c\
	ft_staduptop.c\
	ft_staisempty.c\
	ft_staiter.c\
	ft_stamatch.c\
	ft_stanew.c\
	ft_stapeek.c\
	ft_stapop.c\
	ft_stapush.c\
	ft_staroll_left.c\
	ft_staroll_right.c\
	ft_stasize.c\
	ft_staswap.c

OBJ    := $(SRC:.c=.o)
OBJPRI := ft_dprintf.o\
	ft_printf.o\
	ft_snprintf.o\
	ft_sprintf.o
OBJLST := $(SRCLST:.c=.o)
OBJBST := $(SRCBST:.c=.o)
OBJSTA := $(SRCSTA:.c=.o)

MKFILE := $(lastword $(MAKEFILE_LIST))

# **************************************************************************** #

# Primary targets:

all: $(NAME) list bintree stack

$(NAME) $(LIST) $(BSTREE):: $(MKFILE)
	@if [ -f "$@" ]; then $(MAKE) --no-print-directory fclean; fi

list: $(LIST)

bintree: $(BSTREE)

stack: $(STACK)

$(NAME):: $(OBJ)
	$(AR) $@ $?

$(LIST):: $(OBJLST)
	$(AR) $(NAME) $?
	@$(TC) $(LIST)

$(BSTREE):: $(OBJBST)
	$(AR) $(NAME) $?
	@$(TC) $(BSTREE)

$(STACK):: $(OBJSTA)
	$(AR) $(NAME) $?
	@$(TC) $(STACK)

clean:
	$(RM) $(OBJ) $(OBJLST) $(OBJBST) $(OBJSTA)
	@$(RM) $(LIST) $(BSTREE) $(STACK)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all list bintree stack clean fclean re

# **************************************************************************** #

# Build prerequisites:

$(OBJ): $(HEADER)

$(OBJPRI): $(HDRPRI)

$(OBJLST): $(HDRLST)

$(OBJBST): $(HDRBST)

$(OBJSTA): $(HDRSTA)

ft_getnextline_fd.o: %.o: %.h
