NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline
RM = rm -f
INCLUDES = -I./includes/ -I./libft/includes/

SRCS = main.c \
	./tokenizing/tokenizing.c ./tokenizing/clean_tokens.c \
	./tokenizing/print_tokens.c ./tokenizing/tokenizing_utils.c \
	./tokenizing/handle_pipe_redir.c ./tokenizing/handle_quotes.c \
	./tokenizing/handle_variable.c ./tokenizing/handle_word.c \
	./parsing/parsing.c ./parsing/print_ast.c ./parsing/addArg.c \
	./parsing/addRedir.c ./parsing/cleanAST.c ./parsing/createNode.c \
	./parsing/isRedirection.c ./parsing/parseCommand.c \
	./parsing/parseExpression.c ./parsing/parseRedirection.c \
	./signals/setup_signals.c \
	./exec/exec.c ./exec/exec_builtin.c ./exec/built_ins/builtin_pwd.c \
	./exec/exec_pipe.c ./exec/exec_non_builtin.c ./exec/exec_utils.c \
	./env/envp_to_array.c ./env/env_util.c ./env/init_envp.c

OBJ_DIR = ./obj

OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT = ./libft/libft.a

all: $(NAME)
$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/tokenizing $(OBJ_DIR)/parsing $(OBJ_DIR)/expanding \
	$(OBJ_DIR)/signals $(OBJ_DIR)/exec $(OBJ_DIR)/exec/built_ins

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
