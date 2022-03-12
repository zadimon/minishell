/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 14:05:41 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/03/04 14:26:49 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*away_slash(char *s, int *i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(s, 0, *i);
	tmp2 = ft_strdup(s + *i + 1);
	free(s);
	s = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (s);
}

char	*away_dou_quo(char *s, int *i)
{
	int		j;
	char	*tmp;

	j = *i;
	while (s[++(*i)] != '\0')
	{
		if (s[*i] == '\\' && (s[*i + 1] == '\"'
				|| s[*i + 1] == '$' || s[*i + 1] == '\\'))
		{
			s = away_slash(s, i);
			(*i)++;
		}
		if (s[*i] == '\"')
			break ;
	}
	tmp = ft_threestrcat(ft_substr(s, 0, j),
			ft_substr(s, j + 1, *i - j - 1), ft_strdup(s + *i + 1));
	free(s);
	s = tmp;
	(*i)--;
	return (s);
}

char	*away_sin_quo(char *s, int *i)
{
	int		j;
	char	*tmp;

	j = *i;
	while (s[++(*i)] != '\0')
	{
		if (s[*i] == '\'')
			break ;
	}
	tmp = ft_threestrcat(ft_substr(s, 0, j),
			ft_substr(s, j + 1, *i - j - 1), ft_strdup(s + *i + 1));
	free(s);
	s = tmp;
	(*i)--;
	return (s);
}

char	*start_parser(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			s = away_sin_quo(s, &i);
			continue ;
		}
		if (s[i] == '\"')
		{
			s = away_dou_quo(s, &i);
			continue ;
		}
		if (s[i] == '\\')
			s = away_slash(s, &i);
		i++;
	}
	return (s);
}

void	parser(char *s)
{
	int		i;
	char	*res;

	i = 0;
	if (preparser(s))
	{
		free(s);
		return ;
	}
	res = start_parser(s);
	printf("after %s\n", res);
	free(res);
}
