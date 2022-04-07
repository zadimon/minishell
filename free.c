/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:14:35 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/07 04:37:49 by ebhakaz          ###   ########.fr       */
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

void	ft_free(t_parser *parser)
{
	t_cmd	*next_cmd;
	t_rd	*next_rd;

	free(parser->s);
	if (parser->paths)
		ft_free_str_arr(parser->paths);
	if (!(parser->cmd))
		return ;
	while (parser->cmd != 0)
	{
		next_cmd = parser->cmd->next;
		while (parser->cmd->rd != 0)
		{
			next_rd = parser->cmd->rd->next;
			free(parser->cmd->rd->file_name);
			free(parser->cmd->rd->is_amb);
			free(parser->cmd->rd);
			parser->cmd->rd = next_rd;
		}
		if (parser->cmd->str)
			ft_free_str_arr(parser->cmd->str);
		free(parser->cmd->infile);
		free(parser->cmd->outfile);
		free(parser->cmd->is_amb);
		free(parser->cmd);
		parser->cmd = next_cmd;
	}
}
