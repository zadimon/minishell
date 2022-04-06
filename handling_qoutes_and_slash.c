/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_qoutes_and_slash.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 01:57:06 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/03/28 18:24:04 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*away_slash(char *str, int *i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	free(str);
	str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (str);
}

char	*change_str(char *str, int j, int *i)
{
	char	*res;

	res = ft_threestrcat(ft_substr(str, 0, j),
			ft_substr(str, j + 1, *i - j - 1),
			ft_strdup(str + *i + 1));
	free(str);
	str = res;
	(*i)--;
	return (res);
}

char	*away_dou_quo(char *str, int *i, t_parser *parser)
{
	int		j;
	char	*res;

	j = *i;
	(*i)++;
	while (str[*i] != '\0')
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"'
				|| str[*i + 1] == '$' || str[*i + 1] == '\\'))
		{
			str = away_slash(str, i);
			(*i)++;
		}
		if (str[*i] == '$')
		{
			str = dollar(str, i, parser);
			continue ;
		}
		if (str[*i] == '\"')
			break ;
		(*i)++;
	}
	res = change_str(str, j, i);
	return (res);
}

char	*away_sin_quo(char *str, int *i)
{
	int		j;
	char	*res;

	j = *i;
	while (str[++(*i)] != '\0')
	{
		if (str[*i] == '\'')
			break ;
	}
	res = change_str(str, j, i);
	return (res);
}
