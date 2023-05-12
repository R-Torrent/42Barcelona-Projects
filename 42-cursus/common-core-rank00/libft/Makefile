# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtorrent <rtorrent@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 20:52:16 by rtorrent          #+#    #+#              #
#    Updated: 2023/05/12 16:18:38 by rtorrent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Tools and options:

CFLAGS += -Werror -Wextra -Wall

AR     := ar rcs
RM     := rm -f

# **************************************************************************** #

# Filenames:

NAME0  := libft
NAME   := $(NAME0).a
HEADER := $(NAME0).h

SRC    := ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_lstadd_back_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstmap_bonus.c\
	ft_lstnew_bonus.c\
	ft_lstsize_bonus.c\
	ft_memchr.c\
	ft_memcpy.c\
	ft_memcmp.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_strchr.c\
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
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c

OBJ    = $(filter-out %_bonus.o,$(SRC:.c=.o))
OBB    = $(filter %_bonus.o,$(SRC:.c=.o))
	
# **************************************************************************** #

# Primary targets:

$(NAME): $(OBJ)
	$(AR) $@ $^

bonus: $(OBB)
	$(AR) $(NAME) $^

all: $(NAME)

clean:
	$(RM) $(OBJ) $(OBB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# **************************************************************************** #

# Build prerequisites:

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: bonus all clean fclean re
