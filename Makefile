NAME = server
CLIENT = client
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -Ilibft

SRC_SERVER = server.c server_utils.c
SRC_CLIENT = client.c client_utils.c
HEADER = minitalk.h

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(LIBFT) $(NAME) $(CLIENT)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME)

$(CLIENT): $(OBJ_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(CLIENT)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	make -C libft fclean
	rm -f $(NAME) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re