/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_for_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:04:51 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/11 22:13:53 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*away_dou_quo_for_heredoc(char *str, int *i)
{
	int		j;
	char	*res;

	j = *i;
	(*i)++;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"'
				|| str[*i + 1] == '\\'))
		{
			str = away_slash(str, i);
			(*i)++;
		}
		if (str[*i] == '\"')
			break ;
		(*i)++;
	}
	res = change_str(str, j, i);
	return (res);
}

char	*choose_quotes(char *str_arr, int *i)
{
	if (str_arr[*i] == '\'')
		str_arr = away_sin_quo(str_arr, i);
	if (str_arr[*i] == '\"')
		str_arr = away_dou_quo_for_heredoc(str_arr, i);
	return (str_arr);
}

char	*get_limiter(char *rd)
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
		if (file_name[i] != '$' && (file_name[i] == '\''
				|| file_name[i] == '\"'))
		{
			file_name = choose_quotes(file_name, &i);
			continue ;
		}
		if (file_name[i] == '\\')
			file_name = away_slash(file_name, &i);
		i++;
	}
	return (file_name);
}
