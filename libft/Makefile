NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE)

SRC = \
	$(addprefix src/, ft_abs.c ft_atoi.c ft_bzero.c ft_free_char_mat.c ft_free_mat.c ft_matlen.c ft_tolower.c ft_toupper.c get_next_line_bonus.c safe_close.c) \
	$(addprefix src/alloc/, ft_calloc.c ft_itoa.c ft_nsplit.c ft_realloc.c ft_split.c ft_strdup.c ft_strjoin.c ft_strtrim.c ft_substr.c) \
	$(addprefix src/lst/, ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c) \
	$(addprefix src/mem/, ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c) \
	$(addprefix src/print/, ft_fprintf_utils.c ft_fprintf.c ft_printf_utils.c ft_printf.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c) \
	$(addprefix src/str/, ft_strchr.c ft_strcmp.c ft_striteri.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c) \
	$(addprefix src/type/, ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c)


INCLUDE = include

OBJ_DIR = ./.obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
