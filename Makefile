CFILES = 	src/main.c \
			src/builtins/pwd.c \
			src/builtins/env.c \
			src/history.c \
			src/signal.c \
			src/fake_globals.c \

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -g
LDFLAGS = -lreadline
OBJ_DIR = Obj
OFILES = $(addprefix $(OBJ_DIR)/,$(notdir $(CFILES:.c=.o)))

$(NAME): $(OBJ_DIR) $(OFILES)
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
	@echo "\033[33mclean\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[33mand\033[0m"
	@echo "\033[33mfclean\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re, loading, banner
