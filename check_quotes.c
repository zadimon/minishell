/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:34:18 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/03/31 19:24:42 by ebhakaz          ###   ########.fr       */
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
	return (4);
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
	return (5);
}

int	check_close_quotes(char *s, int *i)
{
	if (s[*i] == '\'')
		return (check_sin_quotes(s, i));
	if (s[*i] == '\"')
		return (check_dou_quotes(s, i));
	return (0);
}
