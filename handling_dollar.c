/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:58:45 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/05 23:39:29 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*get_global_value(char *key, t_env *env)
{
	char	*tmp;

	while (env != 0)
	{
		if (!ft_strcmp(env->key, key))
			break ;
		env = env->next;
	}
	if (!(env))
		return (0);
	tmp = ft_strdup(env->val);
	return (tmp);
}

char	*put_global_value(char *str, int *i, int j, t_parser *parser)
{
	char	*key;
	char	*tmp;
	int		k;

	if (str[*i] == '?')
	{
		(*i)++;
		tmp = ft_itoa(parser->exit_code);
	}
	else
	{
		key = ft_substr(str, j + 1, *i - j - 1);
		tmp = get_global_value(key, parser->env);
		free(key);
	}
	k = ft_strlen(tmp);
	key = ft_threestrcat(ft_substr(str, 0, j),
			tmp, ft_strdup(str + *i));
	free(str);
	*i = j + k;
	return (key);
}

char	*dollar(char *str, int *i, t_parser *parser)
{
	int		j;
	char	*res;

	j = *i;
	while (str[++(*i)] != '\0')
	{
		if (!ifkey(str[*i]))
			break ;
	}
	if (*i == j + 1 && str[*i] != '?')
		return (str);
	res = put_global_value(str, i, j, parser);
	return (res);
}

void	handle_dollar(t_parser *parser, int start)
{
	while (parser->s[start] != '\0' && parser->s[start] != '|')
	{
		if (parser->s[start] == '\\')
		{
			start = start + 2;
			continue ;
		}
		if (parser->s[start] == '\'')
			skip_sin_quo(parser, &start);
		if (parser->s[start] == '\"')
			skip_dou_quo(parser, &start);
		if (parser->s[start] == '$')
		{
			parser->s = dollar(parser->s, &start, parser);
			continue ;
		}
		start++;
	}
}
