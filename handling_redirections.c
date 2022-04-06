/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 00:03:33 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/05 23:24:22 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_infile_d(t_cmd *this, char *rd, char *file_name)
{
	if (rd[1] == '<')
	{
		if (ft_close(this->infile_d, this->infile) == 1)
			return (this);
		this->infile_d = 0;
		if (this->infile)
			free(this->infile);
		this->infile = ft_strdup(file_name);
	}
	else
	{
		if (ft_close(this->infile_d, this->infile) == 1)
			return (this);
		this->infile_d = open(file_name, O_RDONLY);
		this->error = errno;
		if (this->infile)
			free(this->infile);
		this->infile = ft_strdup(file_name);
	}
	return (this);
}

t_cmd	*get_outfile_d(t_cmd *this, char *rd, char *file_name)
{
	if (rd[1] == '>')
	{
		if (ft_close(this->outfile_d, this->outfile) == 1)
			return (this);
		this->outfile_d = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
		this->error = errno;
		if (this->outfile)
			free(this->outfile);
		this->outfile = ft_strdup(file_name);
	}
	else
	{
		if (ft_close(this->outfile_d, this->outfile) == 1)
			return (this);
		this->outfile_d = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		this->error = errno;
		if (this->outfile)
			free(this->outfile);
		this->outfile = ft_strdup(file_name);
	}
	return (this);
}

t_cmd	*open_file(t_cmd *this, char *rd, t_parser *parser)
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
	free(rd);
	free(file_name);
	return (this);
}

t_cmd	*init_fd(t_cmd *this)
{
	this->infile = 0;
	this->infile_d = -2;
	this->outfile = 0;
	this->outfile_d = -2;
	this->is_amb = 0;
	return (this);
}

t_cmd	*make_redirections(t_parser *parser, t_cmd *this, int start)
{
	char	*rd;

	this = init_fd(this);
	while (parser->s[start] != '|' && parser->s[start] != '\0')
	{
		if (parser->s[start] == '<' || parser->s[start] == '>')
		{
			rd = get_redirection(parser, start);
			this = open_file(this, rd, parser);
			if (this->infile_d == -1 || this->outfile_d == -1)
				break ;
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
