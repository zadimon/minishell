/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:03:33 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/13 18:55:24 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rd	*get_infile_d(t_rd *this, char *rd, t_parser *parser)
{
	if (rd[1] == '<')
	{
		this->which_case = HEREDOC_CASE;
		this->file_name = get_limiter(rd);
		if (this->file_name[0] != '\0')
		{
			free(this->is_amb);
			this->is_amb = 0;
		}
	}
	else
	{
		this->which_case = INFILE_CASE;
		this->file_name = get_file_name(rd, parser);
		if (this->file_name[0] != '\0')
		{
			free(this->is_amb);
			this->is_amb = 0;
		}
	}
	return (this);
}

t_rd	*get_outfile_d(t_rd *this, char *rd, t_parser *parser)
{
	if (rd[1] == '>')
	{
		this->which_case = APPEND_CASE;
		this->file_name = get_file_name(rd, parser);
		if (this->file_name[0] != '\0')
		{
			free(this->is_amb);
			this->is_amb = 0;
		}
	}
	else
	{
		this->which_case = OUTFILE_CASE;
		this->file_name = get_file_name(rd, parser);
		if (this->file_name[0] != '\0')
		{
			free(this->is_amb);
			this->is_amb = 0;
		}
	}
	return (this);
}

t_rd	*make_rd_struct(t_rd *this, char *rd, t_parser *parser)
{
	this = check_ambiguous_redirect(this, rd);
	if (rd[0] == '<')
		this = get_infile_d(this, rd, parser);
	else if (rd[0] == '>')
		this = get_outfile_d(this, rd, parser);
	else
	{
		this->file_name = NULL;
		this->is_amb = NULL;
		this->which_case = 0;
	}
	free(rd);
	return (this);
}

t_rd	*add_last_rd(t_rd *this, char *rd, t_parser *parser)
{
	t_rd	*tmp;

	tmp = this;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_rd));
		tmp->next = make_rd_struct(tmp->next, rd, parser);
		tmp->next->next = NULL;
	}
	else
	{
		this = malloc(sizeof(t_rd));
		this = make_rd_struct(this, rd, parser);
		this->next = NULL;
	}
	return (this);
}

t_cmd	*make_redirections(t_parser *parser, t_cmd *this, int start)
{
	char	*rd;

	while (parser->s[start] != '|' && parser->s[start] != '\0')
	{
		if (parser->s[start] == '<' || parser->s[start] == '>')
		{
			rd = get_redirection(parser, start);
			this->rd = add_last_rd(this->rd, rd, parser);
			continue ;
		}
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
	return (this);
}
