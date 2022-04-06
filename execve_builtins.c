/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 00:02:01 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/06 19:23:13 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_builtins(char **argv, t_env *env_lst, int builtin)
{
	if (builtin == 1)
	{
		if (num_of_args(argv) > 1)
			return (cd(&argv[1], env_lst));
		else
			cd(NULL, env_lst);
	}
	else if (builtin == 2)
		return (pwd(&argv[0]));
	else if (builtin == 3)
		return (echo(argv[1], &argv[1]));
	else if (builtin == 4)
		return (export(&argv[1], env_lst));
	else if (builtin == 5)
		return (unset(&argv[1], env_lst));
	else if (builtin == 6)
		return (env(&argv[1], env_lst));
	else if (builtin == 7)
		return (ft_exit(&argv[1], env_lst));
	return (1);
}

int	choose_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->str[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->str[0], "pwd"))
		return (2);
	else if (!ft_strcmp(cmd->str[0], "echo"))
		return (3);
	else if (!ft_strcmp(cmd->str[0], "export"))
		return (4);
	else if (!ft_strcmp(cmd->str[0], "unset"))
		return (5);
	else if (!ft_strcmp(cmd->str[0], "env"))
		return (6);
	else if (!ft_strcmp(cmd->str[0], "exit"))
		return (7);
	return (0);
}
