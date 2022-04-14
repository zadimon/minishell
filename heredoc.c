/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 19:50:15 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/14 15:22:13 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_in_pipe(t_rd *rd, int *fd)
{
	char	*line;

	while (1)
	{
		rl_on_new_line();
		line = readline("\033[1m\033[149;33m>\033[0m ");
		if (!(line) || ft_strcmp(line, rd->file_name) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

int	child_for_heredoc(t_rd *rd, t_parser *parser, int *fd)
{
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		put_error();
	pid = fork();
	if (pid != 0)
	{
		signal(SIGINT, empty);
		signal(SIGQUIT, SIG_IGN);
	}
	if (pid == 0)
	{
		signal(SIGINT, int_heredoc);
		signal(SIGQUIT, SIG_IGN);
		write_in_pipe(rd, fd);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	get_exit_code(status, parser);
	if (parser->exit_code == 1)
		return (1);
	return (0);
}

int	start_heredoc(t_cmd *cmd, t_rd *rd, t_parser *parser, int *fd)
{
	if (cmd->infile_d > 0)
		ft_close(cmd->infile_d, cmd->infile);
	free(cmd->infile);
	free(cmd->is_amb);
	cmd->infile_d = 0;
	cmd->infile = ft_strdup(rd->file_name);
	cmd->is_amb = ft_strdup(rd->is_amb);
	if (child_for_heredoc(rd, parser, fd))
	{
		ft_close(fd[1], NULL);
		ft_close(fd[0], NULL);
		return (1);
	}
	ft_close(fd[1], NULL);
	return (0);
}

int	heredoc(t_parser *parser)
{
	t_cmd	*cmd_tmp;
	t_rd	*rd_tmp;
	int		fd[2];

	cmd_tmp = parser->cmd;
	while (cmd_tmp != 0)
	{
		rd_tmp = cmd_tmp->rd;
		while (rd_tmp != 0)
		{
			if (rd_tmp->which_case == HEREDOC_CASE)
			{
				ft_close(cmd_tmp->heredoc, NULL);
				if (start_heredoc(cmd_tmp, rd_tmp, parser, fd))
					return (1);
				cmd_tmp->heredoc = fd[0];
			}
			rd_tmp = rd_tmp->next;
		}
		cmd_tmp = cmd_tmp->next;
	}
	return (0);
}
