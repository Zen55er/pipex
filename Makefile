NAME = 			pipex
LIBFT_DIR =		../libft_new
LIBFT =			../libft_new/libft.a
SRC =			pipex.c
CC =			@cc
CFLAGS =		-Wall -Werror -Wextra -g

all: ($NAME)

$(NAME): 
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
		@(CC) -o $@ $(LIBFT) -fsanitize=address

%.o: 	%.c
		@(CC) -c -o $@ $< $(CFLAGS)

clean:
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

fclean:	clean
		@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

re:		fclean all

.PHONY: all cleam fclean re