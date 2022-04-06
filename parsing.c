/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:05:41 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/06 01:20:43 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parser(char *s, t_parser *parser)
{
	parser->s = s;
	parser->cmd = 0;
	parser->paths = 0;
	parser->paths = 0;
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
		if (parser->s[start] == '|')
			start++;
		else
		{
			init_cmd(parser, start);
			while (parser->s[start] != '|' && parser->s[start] != '\0')
				start++;
		}
	}
}

void	check(t_parser *parser)
{
	t_cmd	*tmp;
	int		i;

	tmp = parser->cmd;
	printf("\n/*-----*/\n\n");
	while (tmp != 0)
	{
		i = 0;
		printf("str->\t\t");
		while (tmp->str[i])
		{
			printf(":%s:\t\t", tmp->str[i]);
			i++;
		}
		printf("\n");
		printf("infile->\t%s\t\tfd->\t\t%d\n", tmp->infile, tmp->infile_d);
		printf("outfile->\t%s\t\tfd->\t\t%d\n", tmp->outfile, tmp->outfile_d);
		tmp = tmp->next;
	}
	printf("\n/*-----*/\n");
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
		return ;
	}
	start_parsing(parser);
	// check(parser);
	execute_commads(parser);
	ft_free(parser);
}
