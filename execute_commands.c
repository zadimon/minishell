/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:18:29 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/13 18:17:49 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_fd(t_parser *parser, t_cmd *cmd)
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
	if (parser->dup[0] && cmd->infile_d == -2)
		if (dup2(parser->dup[0], STDIN_FILENO) == -1)
			return (put_error());
	if (parser->dup[1] != 1 && cmd->outfile_d == -2)
		if (dup2(parser->dup[1], STDOUT_FILENO) == -1)
			return (put_error());
	if (parser->dup[0] && cmd->infile_d == -2)
		ft_close(parser->dup[0], NULL);
	if (parser->dup[1] != 1 && cmd->outfile_d == -2)
		ft_close(parser->dup[1], NULL);
	if (cmd->next != 0 || cmd->outfile_d == -2)
		ft_close(parser->fdd[0], NULL);
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

void	run_child(t_parser *parser, t_cmd *cmd, int builtin)
{
	char	**envp;

	if (change_fd(parser, cmd) == 1)
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

	parser->fdd[0] = 0;
	parser->fdd[1] = 1;
	parser->dup[0] = 0;
	parser->dup[1] = 1;
	builtin = choose_builtin(cmd);
	if (cmd->next != 0)
		pipe(parser->fdd);
	parser->dup[0] = parser->prev;
	parser->dup[1] = parser->fdd[1];
	parser->prev = parser->fdd[0];
	open_files(cmd);
	parser->pid[i] = fork();
	sig_handle(parser->pid[i]);
	if (parser->pid[i] < 0)
		put_error();
	if (parser->pid[i] == 0)
		run_child(parser, cmd, builtin);
	if (parser->dup[0])
		ft_close(parser->dup[0], NULL);
	if (parser->dup[1] != 1)
		ft_close(parser->dup[1], NULL);
}

void	execute_commads(t_parser *parser)
{
	t_cmd	*cmd;
	int		i;

	if (preexecute(parser))
		return ;
	cmd = parser->cmd;
	i = 0;
	while (cmd != 0)
	{
		execute_one_commad(parser, cmd, i);
		close_files(cmd);
		cmd = cmd->next;
		i++;
	}
	ft_waitpid(parser);
}
