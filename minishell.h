/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:33:50 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/06 19:25:00 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# define CLOSE "\033[0m"
# define BLOD  "\033[1m"
# define COLOR(x,y) "\033["#x";"#y"m"

typedef struct s_env
{
	char			*key;
	char			*val;
	int				index;
	int				flag;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**str;
	struct s_cmd	*next;
	int				infile_d;
	char			*infile;
	int				outfile_d;
	char			*outfile;
	char			*is_amb;
	int				error;
}					t_cmd;

typedef struct s_parser
{
	char	*s;
	t_cmd	*cmd;
	t_env	*env;
	int		exit_code;
	pid_t	pid;
	char	**paths;
	int		fd[2];
	int		prev_pipe;
}			t_parser;

/*-----make str arr-----*/

void	parsing(char *s, t_parser *parser);
void	init_parser(char *s, t_parser *parser);
void	start_parser(t_parser *parser);
void	skip_sin_quo(t_parser *parser, int *end);
void	skip_dou_quo(t_parser *parser, int *end);
void	init_cmd(t_parser *parser, int start);
int		get_str_arr_size(t_parser *parser, int start);
int		find_str_end(t_parser *parser, int end);
char	**make_str_arr(t_parser *parser, int start);
char	*choose_spec_sym(char *str_arr, int *i, t_parser *parser);
char	**parse_str_arr(char **str_arr, int size, t_parser *parser);

/*-----make redirections-----*/

t_cmd	*make_redirections(t_parser *parser, t_cmd *this, int start);
t_cmd	*init_fd(t_cmd *this);
t_cmd	*open_file(t_cmd *this, char *rd, t_parser *parser);
char	*get_redirection(t_parser *parser, int start);
int		find_end_of_redirection(t_parser *parser, int t2);
char	*get_file_name(char *rd, t_parser *parser);
t_cmd	*get_infile_d(t_cmd *this, char *rd, char *file_name);
t_cmd	*get_outfile_d(t_cmd *this, char *rd, char *file_name);
t_cmd	*check_ambiguous_redirect(t_cmd *this, char *rd);

/*-----parsing-----*/

char	*away_sin_quo(char *str, int *i);
char	*away_slash(char *str, int *i);
char	*away_dou_quo(char *str, int *i, t_parser *parser);
char	*change_str(char *str, int j, int *i);
char	*ft_threestrcat(char *s1, char *s2, char *s3);

/*-----free-----*/

void	ft_free_str_arr(char **str_arr);
void	ft_free(t_parser *parser);

/*-----parse dollar-----*/

char	*dollar(char *str, int *i, t_parser *parser);
int		ifkey(char c);
char	*get_global_value(char *key, t_env *env);
char	*put_global_value(char *str, int *i, int j, t_parser *parser);
void	handle_dollar(t_parser *parser, int start);

/*-----check valid str-----*/

int		preparsing(char *c);
int		put_syntax_error(char c);
int		put_syntax_error_str(char c);
int		put_syntax_error_newline(char c);
int		start_preparser(char *s, int *i);
int		check_str(char *s, int *i);
int		check_close_quotes(char *s, int *i);
int		check_sin_quotes(char *s, int *i);
int		check_dou_quotes(char *s, int *i);
int		check_rd_p(char *s, int *i);
int		check_double_pipe(char *s, int *i);
int		check_end_start(char *s, int *i);
int		check_redirections(char *s, int *i);

/*-----execute-----*/

int		ft_close(int fd, char *file_name);
int		put_error(void);
int		put_open_error(char *file_name, char *amb, int error);
void	put_execve_error(char *cmd);
void	add_slash(t_parser *parser);
void	find_paths(t_parser *parser);
void	execute_commads(t_parser *parser);
void	run_child(t_parser *parser, t_cmd *cmd, int num);
int		change_fd(t_parser *parser, t_cmd *cmd, int num);
void	execve_binary_files(t_parser *parser, t_cmd *cmd);
void	close_files(t_cmd *cmd);
int		execve_builtins(char **argv, t_env *env_lst, int builtin);
int		choose_builtin(t_cmd *cmd);
void	get_exit_code(t_cmd *cmd, int status, int w_case, t_parser *parser);

void	rl_replace_line (const char *text, int clear_undo);
int		p_error(char *s1, int errnum, char *msg, char *s2);
void	free_envlst(t_env *lst);
int		num_of_args(char **argv);
int		findkey_env(t_env *env, char *key, int edit);
t_env	*env_to_envlst(char **envp);
t_env	*env_lstlast(t_env *lst);
int		add_pwd_oldpw(t_env *env, char *key, char *val);
t_env	*env_lstnew(char *content);
int		check_argv(char *argv, char c, char *name_bin);
int		print_export(t_env *env, int size);
t_env	*create_first_elment(char *str);
int		sort_export(t_env *env, int size);
int		get_size_envp(t_env *env);
void    handler(int signal);
char	*get_valenv(char *key, t_env *env);

/*builtins*/

int		cd(char **args, t_env *env);
int		echo(char *option, char **args);
int		pwd(char **args);
int		export(char **argv, t_env *env);
int		unset(char **argv, t_env *env);
int		env(char **argv, t_env *env);
int		ft_exit(char **argv, t_env *env);

#endif
