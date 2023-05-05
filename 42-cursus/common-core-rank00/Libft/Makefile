NAME = libft.a
SRC = ft_atoi.c\
 	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_tolower.c\
	ft_toupper.c

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
