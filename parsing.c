/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:05:41 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/11 16:35:00 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parser(char *s, t_parser *parser)
{
	parser->s = s;
	parser->cmd = NULL;
	parser->paths = NULL;
	find_paths(parser);
}

void	start_parsing(t_parser *parser)
{
	int	start;

	start = 0;
	while (parser->s[start] != '\0')
	{
		while (parser->s[start] == ' ' || parser->s[start] == '\t')
			start++;
		init_cmd(parser, start);
		while (parser->s[start] != '|' && parser->s[start] != '\0')
		{
			if (parser->s[start] == '\\')
			{
				start = start + 2;
				continue ;
			}
			if (parser->s[start] == '\'')
				skip_sin_quo(parser, &start);
			if (parser->s[start] == '\"')
				skip_dou_quo(parser, &start);
			start++;
		}
		if (parser->s[start] == '|')
			start++;
	}
}

void	parsing(char *s, t_parser *parser)
{
	init_parser(s, parser);
	if (!(parser->s))
	{
		ft_free(parser);
		return ;
	}
	if (preparsing(parser->s))
	{
		ft_free(parser);
		parser->exit_code = EXIT_SYNTAX_ERROR;
		return ;
	}
	start_parsing(parser);
	execute_commads(parser);
	ft_free(parser);
}
