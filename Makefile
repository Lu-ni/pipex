NAME = libftprintf.a
CC = cc
CFLAGS = -Wextra -Werror -Wall -c
SRC = ft_printf.c hexadecimal_tools.c ft_u_itoa.c ft_print_pucxx.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	# Extract object files from libft.a
	ar -x $(LIBFT)
	# Create libftprintf.a including those object files
	ar -rcs $(NAME) $(OBJ) *.o
	# Optionally, remove extracted object files to clean up
	rm -f *.o "__.SYMDEF SORTED"

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC)

$(LIBFT):
	cd libft && make bonus && cd ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

