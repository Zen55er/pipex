NAME = 			pipex
LIBFT_DIR =		../libft_new
LIBFT =			../libft_new/libft.a
SRC =			pipex.c
SRC_OBJS =		$(SRC:.c=.o)
CC =			@cc
CFLAGS =		-Wall -Wextra -Werror -g

all:	$(NAME)

$(NAME):	$(SRC_OBJS)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@(CC) $(CFLAGS) -o $(@) $(LIBFT) -fsanitize=address

clean:
			@rm -f $(SRC_OBJS)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:	clean
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:		fclean all

.PHONY: all clean fclean re