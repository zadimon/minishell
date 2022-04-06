/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:59:12 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/04 22:19:31 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_str_arr_size(t_parser *parser, int start)
{
	int	i;
	int	size;

	i = start;
	size = 0;
	if (parser->s[i] != ' ' && parser->s[i] != '\t'
		&& parser->s[i] != '|' && parser->s[i] != '\0')
		size++;
	while (parser->s[i] != '|' && parser->s[i] != '\0')
	{
		if (i != start && parser->s[i] != ' ' && parser->s[i] != '\t'
			&& (parser->s[i - 1] == ' ' || parser->s[i - 1] == '\t'))
			size++;
		if (parser->s[i] == '\\')
		{
			i = i + 2;
			continue ;
		}
		if (parser->s[i] == '\'')
			skip_sin_quo(parser, &i);
		if (parser->s[i] == '\"')
			skip_dou_quo(parser, &i);
		i++;
	}
	return (size);
}

int	find_str_end(t_parser *parser, int end)
{
	while (parser->s[end] != ' ' && parser->s[end] != '\t'
		&& parser->s[end] != '|' && parser->s[end] != '\0')
	{
		if (parser->s[end] == '\\')
		{
			end = end + 2;
			continue ;
		}
		if (parser->s[end] == '\'')
			skip_sin_quo(parser, &end);
		if (parser->s[end] == '\"')
			skip_dou_quo(parser, &end);
		end++;
	}
	return (end);
}

char	*choose_spec_sym(char *str_arr, int *i, t_parser *parser)
{
	if (str_arr[*i] == '\'')
		str_arr = away_sin_quo(str_arr, i);
	if (str_arr[*i] == '\"')
		str_arr = away_dou_quo(str_arr, i, parser);
	if (str_arr[*i] == '$')
		str_arr = dollar(str_arr, i, parser);
	return (str_arr);
}

char	**parse_str_arr(char **str_arr, int size, t_parser *parser)
{
	int		k;
	int		i;

	k = 0;
	while (k < size)
	{
		i = 0;
		while (str_arr[k][i] != '\0')
		{
			if (str_arr[k][i] == '\'' || str_arr[k][i] == '\"'
				|| str_arr[k][i] == '$')
			{
				str_arr[k] = choose_spec_sym(str_arr[k], &i, parser);
				continue ;
			}
			if (str_arr[k][i] == '\\')
				str_arr[k] = away_slash(str_arr[k], &i);
			i++;
		}
		k++;
	}
	return (str_arr);
}

char	**make_str_arr(t_parser *parser, int start)
{
	int		size;
	int		i;
	int		k;
	char	**res;

	handle_dollar(parser, start);
	size = get_str_arr_size(parser, start);
	res = malloc(sizeof(char **) * (size + 1));
	k = 0;
	while (k < size)
	{
		while (parser->s[start] == ' ' || parser->s[start] == '\t')
			start++;
		i = find_str_end(parser, start);
		res[k] = ft_substr(parser->s, start, i - start);
		start = i;
		k++;
	}
	res[k] = 0;
	return (parse_str_arr(res, size, parser));
}
