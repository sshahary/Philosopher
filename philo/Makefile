NAME = philo
CC = gcc
CFLAGS = -Werror -Wextra -Wall -fsanitize=thread
LDFLAGS = -pthread -g3
SRC = philo.c utilis.c threadhandler.c utilis2.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re