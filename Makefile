NAME = Connect4
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)/include 

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

SRCS = main.c player.c ai.c
HEADERS = connect4.h

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(LIBFT) $(SRCS) $(HEADERS)
	@echo "Compiling executable..."
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	@echo "Removing object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

debug: fclean
	@$(CC) $(CCFLAGS) -g $(SRCS) -o $(NAME)

.PHONY: all clean fclean re debug
.SILENT:
