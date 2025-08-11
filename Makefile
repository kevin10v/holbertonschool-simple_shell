CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
SRC = main.c input.c execute.c path.c builtins.c string_utils.c errors.c
OBJ = $(SRC:.c=.o)
BIN = hsh

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN)

re: fclean all

.PHONY: all clean fclean re
