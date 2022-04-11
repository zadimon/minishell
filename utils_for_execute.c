/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:34:53 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/11 21:14:07 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_cmd *cmd)
{
	int		res;

	res = 0;
	while (cmd != 0)
	{
		cmd = cmd->next;
		res++;
	}
	return (res);
}

void	close_files(t_cmd *cmd, t_parser *parser)
{
	ft_close(parser->prev_pipe, 0);
	ft_close(parser->fd[1], 0);
	if (cmd->infile_d > 0)
		ft_close(cmd->infile_d, cmd->infile);
	if (cmd->outfile_d > 0)
		ft_close(cmd->outfile_d, cmd->outfile);
}

void	ft_waitpid(t_parser *parser)
{
	int		i;
	int		count;
	int		status;

	i = -1;
	count = count_cmd(parser->cmd);
	while (++i < count)
		waitpid(-1, &status, 0);
	free(parser->pid);
	get_exit_code(status, parser);
}

void	sig_handle(int pid)
{
	if (pid != 0)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (pid == 0)
		signal(SIGQUIT, SIG_DFL);
}

int	preexecute(t_parser *parser)
{
	if (heredoc(parser))
		return (1);
	if (check_is_single(parser))
		return (1);
	parser->pid = malloc(sizeof(pid_t) * count_cmd(parser->cmd));
	if (!(parser->pid))
		return (1);
	parser->prev_pipe = 0;
	return (0);
}
