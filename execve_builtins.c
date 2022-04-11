/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 00:02:01 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/10 14:49:50 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_builtins(t_cmd *cmd, t_parser *parser, int builtin)
{
	if (builtin == 1)
		return (pwd(&cmd->str[0]));
	else if (builtin == 2)
		return (echo(cmd->str[1], &cmd->str[1]));
	else if (builtin == 3)
		return (env(&cmd->str[1], parser->env));
	else if (builtin == 4 || builtin == 5)
		return (export(&cmd->str[1], parser->env));
	else if (builtin == 6)
		return (ft_exit(&cmd->str[1], parser->env));
	else if (builtin == 7)
	{
		if (num_of_args(cmd->str) > 1)
			return (cd(&cmd->str[1], parser->env));
		else
			cd(NULL, parser->env);
	}
	else if (builtin == 8)
		return (unset(&cmd->str[1], parser->env));
	return (1);
}

int	choose_builtin(t_cmd *cmd)
{
	if (cmd->str[0] == 0)
		return (0);
	if (!ft_strcmp(cmd->str[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->str[0], "echo"))
		return (2);
	else if (!ft_strcmp(cmd->str[0], "env"))
		return (3);
	else if (!ft_strcmp(cmd->str[0], "export"))
	{
		if (cmd->str[1] == 0)
			return (4);
		if (cmd->str[1] != 0)
			return (5);
	}
	else if (!ft_strcmp(cmd->str[0], "exit"))
		return (6);
	else if (!ft_strcmp(cmd->str[0], "cd"))
		return (7);
	else if (!ft_strcmp(cmd->str[0], "unset"))
		return (8);
	return (0);
}
