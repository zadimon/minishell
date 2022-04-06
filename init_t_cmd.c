/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:46:53 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/04 22:22:59 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_sin_quo(t_parser *parser, int *end)
{
	(*end)++;
	while (parser->s[*end] != '\'')
		(*end)++;
}

void	skip_dou_quo(t_parser *parser, int *end)
{
	(*end)++;
	while (parser->s[*end] != '\"')
	{
		if (parser->s[*end] == '\\')
		{
			*end = *end + 2;
			continue ;
		}
		(*end)++;
	}
}

void	init_cmd(t_parser *parser, int start)
{
	t_cmd	*tmp;

	if (!(parser->cmd))
	{
		parser->cmd = malloc(sizeof(t_cmd));
		parser->cmd = make_redirections(parser, parser->cmd, start);
		parser->cmd->str = make_str_arr(parser, start);
		parser->cmd->next = 0;
	}
	else
	{
		tmp = parser->cmd;
		while (tmp->next != 0)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_cmd));
		tmp->next = make_redirections(parser, tmp->next, start);
		tmp->next->str = make_str_arr(parser, start);
		tmp->next->next = 0;
	}
}
