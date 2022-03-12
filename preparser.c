/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:51:38 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/03/10 20:25:44 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sin_quotes(char *s, int *i)
{
	while (s[++(*i)] != '\0')
	{
		if (s[*i] == '\'')
		{
			(*i)++;
			return (0);
		}
	}
	return (1);
}

int	check_dou_quotes(char *s, int *i)
{
	while (s[++(*i)] != '\0')
	{
		if (s[*i] == '\\' && s[*i + 1] == '\"')
			*i = *i + 2;
		if (s[*i] == '\"' && s[*i - 1] != '\\')
		{
			(*i)++;
			return (0);
		}
	}
	return (2);
}

int	check_close_quotes(char *s, int *i)
{
	int	error;

	error = 0;
	while (s[*i] != '\0')
	{
		if (s[*i] == '\'')
		{
			error = check_sin_quotes(s, i);
			continue ;
		}
		if (s[*i] == '\"')
		{
			error = check_dou_quotes(s, i);
			continue ;
		}
		if ((s[*i] == ';' || s[*i] == '|') && s[*i + 1] == s[*i])
			return (3);
		if ((s[*i] == ';' || s[*i] == '|')
			&& (s[*i + 1] == ';' || s[*i + 1] == '|'))
			return (4);
		if (s[*i] == '\\')
			(*i)++;
		(*i)++;
	}
	return (error);
}

int	preparser(char *s)
{
	int	i;
	int	error;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (s[i - 1] == '\\' && s[i - 2] != '\\')
		return (put_sytax_error('\\'));
	i = 0;
	error = check_close_quotes(s, &i);
	if (error == 1)
		return (put_sytax_error('\''));
	if (error == 2)
		return (put_sytax_error('\"'));
	if (error == 3)
		return (put_sytax_error_str(s[i + 1]));
	if (error == 4)
		return (put_sytax_error(s[i + 1]));
	return (0);
}
