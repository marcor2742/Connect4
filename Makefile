NAME = Connect4
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)/include $(SDL_INC)

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

SDL_DIR = SDL/build
SDL_INC = -ISDL/include
SDL_LIB = -L$(SDL_DIR) -lSDL3

LDFLAGS = $(SDL_LIB) -Wl,-rpath,'$$ORIGIN/SDL/build'

SDL_DIR = SDL/build
SDL_INC = -ISDL/include
SDL_LIB = -L$(SDL_DIR) -lSDL3

LDFLAGS = $(SDL_LIB) -Wl,-rpath,'$$ORIGIN/SDL/build'

SRCS = main.c player.c ai.c
HEADERS = connect4.h

all: $(SDL_DIR) $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(SDL_DIR):
	@git clone https://github.com/libsdl-org/SDL.git
	@echo "Building SDL"
	@mkdir -p $(SDL_DIR)
	@cmake -S SDL -B $(SDL_DIR) -DSDL_SHARED=ON
	@cmake --build $(SDL_DIR)

$(NAME): $(LIBFT) $(SRCS) $(HEADERS)
	@echo "Compiling executable..."
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(LDFLAGS) -o $(NAME)

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
