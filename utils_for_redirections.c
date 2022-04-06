/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 03:20:17 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/05 23:23:30 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_end_of_redirection(t_parser *parser, int t2)
{
	if (parser->s[t2] == '<' || parser->s[t2] == '>')
		t2++;
	while ((parser->s[t2] == ' ' || parser->s[t2] == '\t')
		&& parser->s[t2] != '|' && parser->s[t2] != '\0')
		t2++;
	while (parser->s[t2] != ' ' && parser->s[t2] != '\t'
		&& parser->s[t2] != '<' && parser->s[t2] != '>'
		&& parser->s[t2] != '|' && parser->s[t2] != '\0')
	{
		if (parser->s[t2] == '\\')
		{
			t2 = t2 + 2;
			continue ;
		}
		if (parser->s[t2] == '\'')
			skip_sin_quo(parser, &t2);
		if (parser->s[t2] == '\"')
			skip_dou_quo(parser, &t2);
		t2++;
	}
	return (t2);
}

char	*get_redirection(t_parser *parser, int start)
{
	int		t1;
	int		t2;
	char	*rd;
	char	*tmp1;
	char	*tmp2;

	t1 = start;
	t2 = start + 1;
	t2 = find_end_of_redirection(parser, t2);
	rd = ft_substr(parser->s, t1, t2 - t1);
	tmp1 = ft_substr(parser->s, 0, t1);
	tmp2 = ft_strdup(parser->s + t2);
	free(parser->s);
	parser->s = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (rd);
}

t_cmd	*check_ambiguous_redirect(t_cmd *this, char *rd)
{
	int	i;
	int	j;

	i = 0;
	while (rd[i] != '\0' && rd[i] != '$')
		i++;
	if (rd[i] == '$')
	{
		j = i;
		while (rd[++i] != '\0')
		{
			if (!ifkey(rd[i]))
				break ;
		}
		this->is_amb = ft_substr(rd, j, i - j);
	}
	return (this);
}

char	*get_file_name(char *rd, t_parser *parser)
{
	int		i;
	char	*file_name;

	i = 0;
	while (rd[i] == '<' || rd[i] == '>')
		i++;
	while (rd[i] == ' ' || rd[i] == '\t')
		i++;
	file_name = ft_strdup(rd + i);
	i = 0;
	while (file_name[i] != '\0')
	{
		if (file_name[i] == '\'' || file_name[i] == '\"'
			|| file_name[i] == '$')
		{
			file_name = choose_spec_sym(file_name, &i, parser);
			continue ;
		}
		if (file_name[i] == '\\')
			file_name = away_slash(file_name, &i);
			i++;
	}
	return (file_name);
}
