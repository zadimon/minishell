/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:22:31 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/11 20:31:06 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_change_env(t_parser *parser)
{
	int	builtin;

	builtin = choose_builtin(parser->cmd);
	if (builtin < 5)
		return (0);
	if (parser->cmd->infile_d == -1)
		return (put_open_error(parser->cmd->infile,
				parser->cmd->is_amb, parser->cmd->error));
	if (parser->cmd->outfile_d == -1)
		return (put_open_error(parser->cmd->outfile,
				parser->cmd->is_amb, parser->cmd->error));
	parser->exit_code = execve_builtins(parser->cmd, parser, builtin);
	if (parser->paths)
		ft_free_str_arr(parser->paths);
	parser->paths = 0;
	find_paths(parser);
	return (1);
}

int	check_is_single(t_parser *parser)
{
	int		count;
	t_cmd	*tmp;

	tmp = parser->cmd;
	count = count_cmd(tmp);
	if (count == 1)
		if (if_change_env(parser) == 1)
			return (1);
	return (0);
}
