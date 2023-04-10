NAME =			pipex
LIBFT_DIR =		../libft_new
LIBFT =			../libft_new/libft.a
SRC =			pipex.c pipex_utils.c pipex_utils2.c pipex_utils3.c
SRC_BONUS =		pipex_bonus.c pipex_utils_bonus.c pipex_utils2_bonus.c pipex_utils3.c
CC = 			@cc
CFLAGS = 		-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME):	$(SRC)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(^) -o $(@) $(LIBFT) -fsanitize=address

bonus:		$(SRC_BONUS)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(^) -o $(NAME) $(LIBFT) -fsanitize=address

clean:
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:		clean
			@rm -f $(NAME)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:			fclean all

reb:		fclean bonus

.PHONY: all clean fclean re