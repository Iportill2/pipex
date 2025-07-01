NAME = pipex

CC = gcc
CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address
RM = rm -rf
LIB = Libft

SRC_DIR = src/

SRCS = $(SRC_DIR)main.c \
       $(SRC_DIR)utils.c \
	   $(SRC_DIR)split.c \
	   $(SRC_DIR)cmd.c \
	   $(SRC_DIR)open_close.c

OBJS = $(SRCS:.c=.o)

.SILENT:

all: $(NAME)

%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)/libft.a

clean:
	make -C $(LIB) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIB) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
