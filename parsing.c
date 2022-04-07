/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:05:41 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/08 01:20:48 by ebhakaz          ###   ########.fr       */
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
	t_cmd	*tmp_cmd;
	t_rd	*tmp_rd;
	int		i;

	tmp_cmd = parser->cmd;
	printf("\n/*-----*/\n\n");
	while (tmp_cmd != 0)
	{
		i = 0;
		printf("str->\t\t");
		while (tmp_cmd->str[i])
		{
			printf(":%s:\t\t", tmp_cmd->str[i]);
			i++;
		}
		printf("\n");
		tmp_rd = tmp_cmd->rd;
		while (tmp_rd != 0)
		{
			printf("file name: %s\t\tcase = %d\t\tis_amb: %s\n",tmp_rd->file_name, tmp_rd->which_case, tmp_rd->is_amb);
			tmp_rd = tmp_rd->next;
		}
		// printf("infile->\t%s\t\tfd->\t\t%d\n", tmp->infile, tmp->infile_d);
		// printf("outfile->\t%s\t\tfd->\t\t%d\n", tmp->outfile, tmp->outfile_d);
		tmp_cmd = tmp_cmd->next;
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
	check(parser);
	execute_commads(parser);
	ft_free(parser);
}
