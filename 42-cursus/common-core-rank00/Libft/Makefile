NAME = libft.a
SRC = ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_memchr.c\
	ft_memcpy.c\
	ft_memcmp.c\
	ft_memmove.c\
	ft_memset.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_substr.c\
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
