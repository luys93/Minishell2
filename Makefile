NAME = minishell

BROWN = \033[1;38;2;101;67;33m
GREEN = \033[1;92m
RED = \033[1;91m
LIGHT_CYAN = \033[1;96m
RESET = \033[0m

CC = cc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilibft -g -gdwarf-4

OBJS_DIR = objs
SRCS_DIR = srcs

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = 	$(SRCS_DIR)/main.c \
		$(SRCS_DIR)/signal.c \
		$(SRCS_DIR)/parse/prompt.c\
		$(SRCS_DIR)/parse/split.c \
		$(SRCS_DIR)/parse/split_utils.c \
		$(SRCS_DIR)/parse/free.c \
		$(SRCS_DIR)/parse/parser.c \
		$(SRCS_DIR)/parse/parse_utils.c \
		$(SRCS_DIR)/parse/parse_utils2.c \
		$(SRCS_DIR)/parse/list_utils.c \
		$(SRCS_DIR)/parse/prove.c \
		$(SRCS_DIR)/parse/expansion.c \
		$(SRCS_DIR)/parse/expansion_utils.c \
		$(SRCS_DIR)/parse/expansion_utils2.c \
		$(SRCS_DIR)/parse/init.c\
		$(SRCS_DIR)/parse/input.c\
		$(SRCS_DIR)/parse/rediraction.c\
		$(SRCS_DIR)/parse/token_utils.c\
		$(SRCS_DIR)/parse/utils.c\
		$(SRCS_DIR)/parse/handle_error.c\
		$(SRCS_DIR)/parse/heredoc.c\
		$(SRCS_DIR)/parse/heredoc_utils.c\
		$(SRCS_DIR)/builtins/check_builtin.c \
		$(SRCS_DIR)/builtins/cd.c \
		$(SRCS_DIR)/builtins/echo.c \
		$(SRCS_DIR)/builtins/env.c \
		$(SRCS_DIR)/builtins/exit.c \
		$(SRCS_DIR)/builtins/export.c \
		$(SRCS_DIR)/builtins/export_utils.c \
		$(SRCS_DIR)/builtins/pwd.c \
		$(SRCS_DIR)/builtins/unset.c \
		$(SRCS_DIR)/builtins/utils.c \
		$(SRCS_DIR)/executor/executor.c \
		$(SRCS_DIR)/executor/command.c \
		$(SRCS_DIR)/executor/redirections.c \
		$(SRCS_DIR)/executor/redirections_utils.c \
		$(SRCS_DIR)/executor/pipe_redir.c \
		$(SRCS_DIR)/executor/check.c \
		$(SRCS_DIR)/executor/utils.c 

OBJ = $(SRC:%.c=$(OBJS_DIR)/%.o)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) -L$(LIBFT_DIR) -lft -lreadline
	@printf "$(GREEN)$(NAME) compiled successfully!$(RESET)\n"

$(LIBFT):
	@printf "$(BROWN)Building libft...$(RESET)\n" 
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: all

clean:
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@printf "$(RED)Object files cleaned!$(RESET)\n"
	
fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(LIGHT_CYAN)Full cleanup done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus