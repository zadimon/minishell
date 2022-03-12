LIBFT_DIR	= ./libft

LIBFT		= ./libft/libft.a

NAME		= minishell

SRC			= main.c\
			  parser.c\
			  utils_for_parser.c\
			  preparser.c

OBJ			= $(SRC:.c=.o)

BOBJ		= $(BSRC:.c=.o)

FLAGS		= -Wall -Wextra -Werror -g

RM			= rm -f

%.o:		%.c minishell.h Makefile
			gcc $(FLAGS) -c $< -o $(<:.c=.o) -I.

all:		$(NAME)

.FORCE:

$(LIBFT):	.FORCE
			$(MAKE) -C $(LIBFT_DIR)

$(NAME):	$(OBJ) $(LIBFT)
			gcc $(FLAGS) -include minishell.h -o $(NAME) $(OBJ) $(LIBFT)

clean:
			$(MAKE) clean -C $(LIBFT_DIR)
			$(RM) $(OBJ) $(BOBJ)

fclean:		clean
			$(MAKE) fclean -C $(LIBFT_DIR)
			$(RM) $(NAME) $(BNAME)

re:			fclean all

.PHONY:		all clean fclean re