NAME = pipex
CC = cc
CFLAGS = -Wextra -Werror -Wall
SRC = main.c parser.c cmd_utils.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L. -lft -o $(NAME)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

$(LIBFT):
	cd libft && make bonus && cd ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

