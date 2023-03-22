NAME =			pipex
LIBFT_DIR =		../libft_new
LIBFT =			../libft_new/libft.a
SRC =			pipex.c pipex_utils.c
CC = 			@cc
CFLAGS = 		-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME):	$(SRC)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(^) -o $(@) $(LIBFT) -fsanitize=address

clean:
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:		clean
			@rm -f $(NAME)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY: all clean fclean re