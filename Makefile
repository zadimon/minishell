LIBFT_DIR	= ./libft

LIBFT		= ./libft/libft.a

NAME		= minishell

INC			= ./minishell.h

SRC			= utils_for_parser.c\
			  put_syntax_error.c\
			  preparsing.c\
			  check_quotes.c\
			  check_redirections_and_pipes.c\
			  parsing.c\
			  free.c\
			  init_t_cmd.c\
			  make_str_arr.c\
			  handling_qoutes_and_slash.c\
			  handling_dollar.c\
			  handling_redirections.c\
			  utils_for_redirections.c\
			  put_errors.c\
			  execute_commands.c\
			  main.c\
			  utils.c\
			  builtin_cd.c\
			  builtin_echo.c\
			  builtin_env.c\
			  builtin_pwd.c\
			  builtin_export.c\
			  builtin_unset.c\
			  builtin_env1.c\
			  builtin_exit.c\
			  sort_export.c\
			  sig_handle.c\
			  execve_builtins.c\
			  get_exit_code.c\
			  builtin_env2.c\
			  utils_for_execute.c\
			  open_files.c\
			  heredoc.c\
			  execute_single_cmd.c

OBJ			= $(SRC:.c=.o)

BOBJ		= $(BSRC:.c=.o)

FLAGS		= -Wall -Wextra -Werror -g -include $(INC)

CC			= gcc

RM			= rm -f

%.o:		%.c $(INC) Makefile
			$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

.PHONY:		all clean fclean re bonus

all:		
			$(MAKE) -C $(LIBFT_DIR) -j 4
			$(MAKE) $(NAME) -j 4

$(NAME):	$(OBJ)
			$(CC) -lreadline $(FLAGS) -o $(NAME) -lreadline -L \
			~/.brew/Cellar/readline/8.1.2/lib -I ~/.brew/Ceallar/readline/8.1.2/include $(OBJ) $(LIBFT)

clean:
			$(MAKE) clean -C $(LIBFT_DIR)
			$(RM) $(OBJ) $(BOBJ)

fclean:		clean
			$(MAKE) fclean -C $(LIBFT_DIR)
			$(RM) $(NAME) $(BNAME)

re:			fclean all

.PHONY:		all clean fclean re