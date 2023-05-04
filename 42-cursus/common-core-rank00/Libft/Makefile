NAME = libft.a
SRC = ft_isalpha.c\
	  ft_isdigit.c
OBJ = $(SRC:.c=.o)
CFLAGS += -Werror -Wextra -Wall

$(NAME): $(OBJ)
	ar -crs $(NAME) $(OBJ)

all: $(NAME)

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.PHONY: add re clean fclean
