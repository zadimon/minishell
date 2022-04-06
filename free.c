/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:14:35 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/04 19:08:32 by ebhakaz          ###   ########.fr       */
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
	t_cmd	*next;

	free(parser->s);
	if (parser->paths)
		ft_free_str_arr(parser->paths);
	if (!(parser->cmd))
		return ;
	while (parser->cmd != 0)
	{
		next = parser->cmd->next;
		free(parser->cmd->infile);
		free(parser->cmd->outfile);
		free(parser->cmd->is_amb);
		if (parser->cmd->str)
			ft_free_str_arr(parser->cmd->str);
		free(parser->cmd);
		parser->cmd = next;
	}
}
