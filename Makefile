CFILES =	src/main.c \
			src/utils.c \
			src/builtins/pwd.c \
			src/builtins/env.c \
			src/builtins/cd.c \
			src/builtins/echo.c \
			src/builtins/unset.c \
			src/builtins/export.c \
			src/builtins/export_utils.c \
			src/builtins/export_utils2.c \
			src/execution/fake_globals.c \
			src/execution/signal.c \
			src/execution/signal2.c \
			src/execution/history.c \
			src/execution/execute_external.c \
			src/execution/external_utils.c \
			src/execution/pipes.c \
			src/execution/pipes_utils.c \
			src/execution/redirection.c \
			src/execution/redirection_utils.c \
			src/execution/heredoc.c \
			src/execution/execute_command.c \
			src/execution/ft_exit.c \
			src/execution/handle_shlvl.c \
			src/parsing/parsing.c \
			src/parsing/parsing_handler.c \
			src/parsing/split_quotes.c \
			src/parsing/split_quotes2.c \
			src/parsing/process_token.c \
			src/parsing/create_linked_list.c \
			src/parsing/create_tabel.c \
			src/parsing/create_tabel2.c \
			src/parsing/create_tabel3.c \
			src/parsing/syntax_errors.c \
			src/parsing/trim_len.c \
			src/parsing/trim_len2.c \
			src/parsing/expand.c \
			src/parsing/expand2.c \
			src/parsing/expand_env.c \
			src/parsing/expand_quotes.c \
			src/parsing/expand_process_arg.c \
			src/parsing/expand_filename.c \



NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -g
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline
OBJ_DIR = Obj
OFILES = $(addprefix $(OBJ_DIR)/,$(notdir $(CFILES:.c=.o)))

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(LIBFT) $(OBJ_DIR) $(OFILES)
	@$(CC) $(OFILES) $(LDFLAGS) -o $(NAME)
	clear
	@$(MAKE)	loading
	clear
	@$(MAKE)	banner


$(OBJ_DIR)/%.o: src/%.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: src/builtins/%.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: src/execution/%.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: src/parsing/%.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

loading:
	@for i in {1..50}; do \
		printf '%s' "██"; \
		sleep 0.01; \
	done

banner:
	@echo "                                                                                                  "
	@echo "   ▄▄▄▄███▄▄▄▄    ▄█  ███▄▄▄▄    ▄█     ▄████████    ▄█    █▄       ▄████████  ▄█        ▄█       "
	@echo " ▄██▀▀▀███▀▀▀██▄ ███  ███▀▀▀██▄ ███    ███    ███   ███    ███     ███    ███ ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███    █▀    ███    ███     ███    █▀  ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄     ███       ███       "
	@echo " ███   ███   ███ ███▌ ███   ███ ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀     ███       ███       "
	@echo " ███   ███   ███ ███  ███   ███ ███           ███   ███    ███     ███    █▄  ███       ███       "
	@echo " ███   ███   ███ ███  ███   ███ ███     ▄█    ███   ███    ███     ███    ███ ███▌    ▄ ███▌    ▄ "
	@echo "  ▀█   ███   █▀  █▀    ▀█   █▀  █▀    ▄████████▀    ███    █▀      ██████████ █████▄▄██ █████▄▄██ "
	@echo "                                                                              ▀         ▀         "
	@echo "                                                                                                  "
	@echo " \033[90mby mhummel & nlewicki\033[0m                                                                            "
	@echo "                                                                                                  "
	@echo "                                                                          \033[36mstart with ./minishell\033[0m  "
	@echo "                                                                                                  "

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OFILES)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[90mclean\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "\033[90mand\033[0m"
	@echo "\033[90mfclean\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re, loading, banner, libft
