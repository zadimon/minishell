/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 00:18:29 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/08 01:13:48 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_cmd *cmd)
{
	t_rd	*tmp;

	tmp = cmd->rd;
	while (tmp != 0)
	{
		if (tmp->which_case == INFILE_CASE)
		{
			if (cmd->infile_d > 0)
				ft_close(cmd->infile_d, cmd->infile);
			free(cmd->infile);
			cmd->infile_d = open(tmp->file_name, O_RDONLY);
			cmd->infile = ft_strdup(tmp->file_name);
			cmd->is_amb = ft_strdup(tmp->is_amb);
		}
		else if (tmp->which_case == HEREDOC_CASE)
		{
			if (cmd->infile_d > 0)
				ft_close(cmd->infile_d, cmd->infile);
			free(cmd->infile);
			cmd->infile_d = 0;
			cmd->infile = ft_strdup(tmp->file_name);
			cmd->is_amb = ft_strdup(tmp->is_amb);
		}
		else if (tmp->which_case == OUTFILE_CASE)
		{
			if (cmd->outfile_d > 0)
				ft_close(cmd->outfile_d, cmd->outfile);
			free(cmd->outfile);
			cmd->outfile_d = open(tmp->file_name,
					O_CREAT | O_RDWR | O_TRUNC, 0644);
			cmd->outfile = ft_strdup(tmp->file_name);
			cmd->is_amb = ft_strdup(tmp->is_amb);
		}
		else if (tmp->which_case == OUTFILE_CASE)
		{
			if (cmd->outfile_d > 0)
				ft_close(cmd->outfile_d, cmd->outfile);
			free(cmd->outfile);
			cmd->outfile_d = open(tmp->file_name,
					O_CREAT | O_RDWR | O_APPEND, 0644);
			cmd->outfile = ft_strdup(tmp->file_name);
			cmd->is_amb = ft_strdup(tmp->is_amb);
		}
		if (cmd->infile_d == -1 || cmd->outfile_d == -1)
			return ;
		tmp = tmp->next;
	}
}

int	change_fd(t_parser *parser, t_cmd *cmd, int num)
{
	open_files(cmd);
	if (cmd->infile_d == -1)
		return (put_open_error(cmd->infile, cmd->is_amb));
	if (cmd->outfile_d == -1)
		return (put_open_error(cmd->outfile, cmd->is_amb));
	if (cmd->infile_d > 0)
		if (dup2(cmd->infile_d, STDIN_FILENO) == -1)
			return (put_error());
	if (cmd->outfile_d > 0)
		if (dup2(cmd->outfile_d, STDOUT_FILENO) == -1)
			return (put_error());
	if (num > 0 && cmd->infile_d < -1)
		if (dup2(parser->prev_pipe, STDIN_FILENO) == -1)
			return (put_error());
	if (cmd->next != 0 && cmd->outfile_d < -1)
		if (dup2(parser->fd[1], STDOUT_FILENO) == -1)
			return (put_error());
	return (0);
}

void	execve_binary_files(t_parser *parser, t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (parser->paths[i])
	{
		tmp = ft_strjoin(parser->paths[i], cmd->str[0]);
		if (access(tmp, 1) == 0)
			execve(tmp, cmd->str, 0);
		free(tmp);
		i++;
	}
}

void	run_child(t_parser *parser, t_cmd *cmd, int num)
{
	printf("Hello from child\n");
	if (change_fd(parser, cmd, num) == 1)
		exit(EXIT_FILE_ERROR);
	if (cmd->str[0] == 0)
		exit(EXIT_SUCCESS);
	if (ft_strchr(cmd->str[0], '/'))
		execve(cmd->str[0], cmd->str, 0);
	else
		execve_binary_files(parser, cmd);
	put_execve_error(cmd->str[0]);
	exit(EXIT_CMD_NOT_FOUND);
}

void	close_files(t_cmd *cmd)
{
	if (cmd->infile_d > 0)
		ft_close(cmd->infile_d, cmd->infile);
	if (cmd->outfile_d > 0)
		ft_close(cmd->outfile_d, cmd->outfile);
}

void	execute_commads(t_parser *parser)
{
	t_cmd	*cmd;
	int		i;
	int		status;

	cmd = parser->cmd;
	i = 0;
	parser->prev_pipe = 0;
	while (cmd != 0)
	{
		if (pipe(parser->fd) == -1)
			put_error();
		parser->pid = fork();
		if (parser->pid < 0)
			put_error();
		if (parser->pid == 0)
			run_child(parser, cmd, i);
		ft_close(parser->prev_pipe, 0);
		ft_close(parser->fd[1], 0);
		close_files(cmd);
		parser->prev_pipe = parser->fd[0];
		cmd = cmd->next;
		i++;
	}
	close(parser->fd[0]);
	waitpid(parser->pid, &status, 0);
	get_exit_code(status, parser);
}
