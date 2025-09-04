NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline
RM = rm -f
INCLUDES = -I./includes/ -I./libft/includes/

SRCS = main.c \
	./tokenizing/tokenizing.c ./tokenizing/clean_tokens.c \
	./tokenizing/print_tokens.c ./tokenizing/tokenizing_utils.c \
	./parsing/parsing.c ./parsing/print_ast.c ./parsing/addArg.c \
	./parsing/addRedir.c ./parsing/cleanAST.c ./parsing/createNode.c \
	./parsing/isRedirection.c ./parsing/parseCommand.c \
	./parsing/parseExpression.c ./parsing/parseRedirection.c \

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
