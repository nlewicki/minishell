CFILES = 	src/main.c \
			src/builtins/pwd.c \
			src/builtins/env.c \
			src/builtins/cd.c \
			src/history.c \
			src/signal.c \
			src/fake_globals.c \
			src/builtins/echo.c \
			src/builtins/unset.c \
			src/builtins/export.c

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -g
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline
OBJ_DIR = Obj
OFILES = $(addprefix $(OBJ_DIR)/,$(notdir $(CFILES:.c=.o)))

LIBFT_DIR = src/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_OBJ_DIR = $(LIBFT_DIR)/Obj_libft
LIBFT_OFILES = $(addprefix $(LIBFT_OBJ_DIR)/,$(notdir $(FILES:.c=.o)))

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

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

loading:
	@for i in {1..42}; do \
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
	@echo " by mhummel & nlewicki                                                                            "
	@echo "                                                                                                  "
	@echo "                                                                          start with ./minishell  "
	@echo "                                                                                                  "

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OFILES)
	@make -C $(LIBFT_DIR) clean
	@echo "\033[33mclean\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "\033[33mand\033[0m"
	@echo "\033[33mfclean\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re, loading, banner, libft
