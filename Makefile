NAME = pipex

CC = gcc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = libft/

SRC = src/pipex_main.c src/ft_error.c src/path_parse.c src/ft_free.c \

OBJS = $(SRC:.c=.o)
	
INCLUDE = -L ./libft -lft

GREEN=\033[1;42m
RED=\033[1;31m
CYAN=\033[1;36m
END=\x1b[0m

S = sleep 0.6

$(NAME): $(OBJS)
		@clear
		@make -C $(LIBFT_DIR)
		@echo "$(CYAN)Compiling libft...$(END)"
		@$(S)
		@echo "$(CYAN)¡Libft successfully compiled!$(END)"
		@$(S)
		@echo "$(CYAN)Compiling Pipex...$(END)"
		@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDE)
		@$(S)
		@echo "$(GREEN)¡Compilation Success, you can run Pipex!$(END)"
	
all: $(NAME)

clean:
		@$(RM) $(OBJS) $(NAME)
		@cd $(LIBFT_DIR) && $(MAKE) clean

fclean: clean
		@$(RM) $(NAME)
		@cd $(LIBFT_DIR) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re bonus