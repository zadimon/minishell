/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:51:38 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/03 17:13:01 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_rd_p(char *s, int *i)
{
	if (s[*i] == '|')
		return (check_double_pipe(s, i));
	if (s[*i] == '<' || s[*i] == '>')
		return (check_redirections(s, i));
	return (0);
}

int	check_end_start(char *s, int *i)
{
	int	error;

	error = 0;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] == '|' || s[*i] == ';')
	{
		if (s[*i + 1] == s[*i])
			return (2);
		return (1);
	}
	while (s[*i] != '\0')
		(*i)++;
	if (s[*i - 1] == '\\' && s[*i - 2] != '\\')
		return (3);
	return (0);
}

int	check_str(char *s, int *i)
{
	int	error;

	error = 0;
	while (s[*i] != '\0')
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			error = check_close_quotes(s, i);
			continue ;
		}
		if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
		{
			error = check_rd_p(s, i);
			if (error == 0)
				continue ;
			return (error);
		}
		if (s[*i] == ';')
			return (7);
		if (s[*i] == '\\')
			(*i)++;
		(*i)++;
	}
	return (error);
}

int	start_preparser(char *s, int *i)
{
	int	error;

	error = 0;
	error = check_end_start(s, i);
	if (error > 0)
		return (error);
	*i = 0;
	error = check_str(s, i);
	return (error);
}

int	preparsing(char *s)
{
	int	i;
	int	error;

	i = 0;
	if (s[i] == '\0')
		return (0);
	error = start_preparser(s, &i);
	if (error == 1 || error == 6 || error == 7 || error == 8 || error == 9)
		return (put_syntax_error(s[i]));
	if (error == 2)
		return (put_syntax_error_str(s[i]));
	if (error == 3)
		return (put_syntax_error('\\'));
	if (error == 4)
		return (put_syntax_error('\''));
	if (error == 5)
		return (put_syntax_error('\"'));
	if (error == 10)
		return (put_syntax_error_newline(s[i]));
	return (0);
}
