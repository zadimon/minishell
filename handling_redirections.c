/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:03:33 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/07 04:54:40 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rd	*get_infile_d(t_rd *this, char *rd, char *file_name)
{
	if (rd[1] == '<')
	{
		this->which_case = HEREDOC_CASE;
		this->file_name = ft_strdup(file_name);
	}
	else
	{
		this->which_case = INFILE_CASE;
		this->file_name = ft_strdup(file_name);
	}
	return (this);
}

t_rd	*get_outfile_d(t_rd *this, char *rd, char *file_name)
{
	if (rd[1] == '>')
	{
		this->which_case = APPEND_CASE;
		this->file_name = ft_strdup(file_name);
	}
	else
	{
		this->which_case = OUTFILE_CASE;
		this->file_name = ft_strdup(file_name);
	}
	return (this);
}

t_rd	*make_rd_struct(t_rd *this, char *rd, t_parser *parser)
{
	char	*file_name;

	this = check_ambiguous_redirect(this, rd);
	file_name = get_file_name(rd, parser);
	if (file_name[0] != '\0')
	{
		free(this->is_amb);
		this->is_amb = 0;
	}
	if (rd[0] == '<')
		this = get_infile_d(this, rd, file_name);
	else if (rd[0] == '>')
		this = get_outfile_d(this, rd, file_name);
	else
	{
		this->file_name = 0;
		this->is_amb = 0;
		this->which_case = 0;
	}
	free(rd);
	free(file_name);
	return (this);
}

t_rd	*add_last_rd(t_rd *this, char *rd, t_parser *parser)
{
	t_rd	*tmp;

	tmp = this;
	if (tmp)
	{
		while (tmp->next != 0)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_rd));
		tmp->next = make_rd_struct(tmp->next, rd, parser);
		tmp->next->next = 0;
	}
	else
	{
		this = malloc(sizeof(t_rd));
		this = make_rd_struct(this, rd, parser);
		this->next = 0;
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
