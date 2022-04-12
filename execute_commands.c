/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:18:29 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/12 20:29:06 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_fd(t_parser *parser, t_cmd *cmd, int i)
{
	if (cmd->infile_d == -1)
		return (put_open_error(cmd->infile, cmd->is_amb, cmd->error));
	if (cmd->outfile_d == -1)
		return (put_open_error(cmd->outfile, cmd->is_amb, cmd->error));
	if (cmd->infile_d > 0)
		if (dup2(cmd->infile_d, STDIN_FILENO) == -1)
			return (put_error());
	if (cmd->outfile_d > 0)
		if (dup2(cmd->outfile_d, STDOUT_FILENO) == -1)
			return (put_error());
	if (i > 0 && cmd->infile_d == -2)
		if (dup2(parser->fd[i - 1][0], STDIN_FILENO) == -1)
			return (put_error());
	if (cmd->next != 0 && cmd->outfile_d == -2)
		if (dup2(parser->fd[i][1], STDOUT_FILENO) == -1)
			return (put_error());
	ft_close_all_pipes(parser, parser->amount - 1);
	return (0);
}

void	execve_binary_files(t_parser *parser, t_cmd *cmd, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	find_paths(parser);
	if (parser->paths != 0)
	{
		while (parser->paths[i])
		{
			tmp = ft_strjoin(parser->paths[i], cmd->str[0]);
			if (access(tmp, 1) == 0)
				execve(tmp, cmd->str, envp);
			free(tmp);
			i++;
		}
	}
	else
		put_execve_error(cmd->str[0], 1);
}

void	run_child(t_parser *parser, t_cmd *cmd, int i, int builtin)
{
	char	**envp;

	open_files(cmd);
	if (change_fd(parser, cmd, i) == 1)
		exit(EXIT_FILE_ERROR);
	if (cmd->str[0] == 0 || builtin > 4)
		exit(EXIT_SUCCESS);
	if (builtin > 0 && builtin < 5)
		exit(execve_builtins(cmd, parser, builtin));
	shlvl(cmd->str[0], parser->env);
	envp = new_envp(parser->env);
	if (ft_strchr(cmd->str[0], '/'))
		execve(cmd->str[0], cmd->str, envp);
	else
		execve_binary_files(parser, cmd, envp);
	put_execve_error(cmd->str[0], 0);
}

void	execute_one_commad(t_parser *parser, t_cmd *cmd, int i)
{
	int	builtin;

	builtin = choose_builtin(cmd);
	parser->pid[i] = fork();
	sig_handle(parser->pid[i]);
	if (parser->pid[i] < 0)
		put_error();
	if (parser->pid[i] == 0)
		run_child(parser, cmd, i, builtin);
}

void	execute_commads(t_parser *parser)
{
	t_cmd	*cmd;
	int		i;

	if (preexecute(parser))
		return ;
	i = 0;
	cmd = parser->cmd;
	while (cmd != 0)
	{
		execute_one_commad(parser, cmd, i);
		close_files(cmd);
		cmd = cmd->next;
		i++;
	}
	ft_close_all_pipes(parser, parser->amount - 1);
	ft_waitpid(parser);
}
