# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubert- <jaubert-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 13:01:15 by jaubert-          #+#    #+#              #
#    Updated: 2023/04/15 22:57:08 by jaubert-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = "rush-02"
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CFLAGS += -Werror -Wextra -Wall

$(NAME): $(OBJ)
		cc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.PHONY: clean fclean
