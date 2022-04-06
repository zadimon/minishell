/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections_and_pipes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 20:31:21 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/01 21:32:34 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_double_pipe(char *s, int *i)
{
	(*i)++;
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i] == '|')
		return (6);
	return (0);
}

int	check_redirections(char *s, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	if (s[start] == '>' && s[*i] == '<')
		return (8);
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (s[*i - 1] != '<' && s[*i - 1] != '>' && (s[*i] == '<' || s[*i] == '>'))
		return (9);
	if ((s[*i - 1] == '<' || s[*i - 1] == '>')
		&& (s[*i] == '<' || s[*i] == '>'))
	{
		if (s[*i + 1] == s[*i])
			return (2);
		if (s[*i + 1] == '<' || s[*i + 1] == '>')
			return (8);
	}
	if (s[*i] == '\0' || s[*i] == '|')
		return (10);
	return (0);
}
