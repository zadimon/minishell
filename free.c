/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:14:35 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/09 14:49:07 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	ft_free_rd(t_rd *tmp)
{
	t_rd	*next_rd;

	while (tmp != 0)
	{
		next_rd = tmp->next;
		free(tmp->file_name);
		free(tmp->is_amb);
		free(tmp);
		tmp = next_rd;
	}
	free(tmp);
}

void	ft_free(t_parser *parser)
{
	t_cmd	*next_cmd;

	free(parser->s);
	if (parser->paths)
		ft_free_str_arr(parser->paths);
	if (!(parser->cmd))
		return ;
	while (parser->cmd != 0)
	{
		next_cmd = parser->cmd->next;
		ft_free_rd(parser->cmd->rd);
		if (parser->cmd->str)
			ft_free_str_arr(parser->cmd->str);
		free(parser->cmd->infile);
		free(parser->cmd->outfile);
		free(parser->cmd->is_amb);
		free(parser->cmd);
		parser->cmd = next_cmd;
	}
}
