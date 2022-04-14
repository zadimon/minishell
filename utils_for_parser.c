/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:25:33 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/14 15:04:24 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_threestrcat(char *s1, char *s2, char *s3)
{
	char	*res;

	if (s2)
	{
		res = ft_strjoin(s1, s2);
		free(s1);
		s1 = ft_strdup(res);
		free(res);
	}
	res = ft_strjoin(s1, s3);
	free(s1);
	free(s2);
	free(s3);
	return (res);
}

void	add_slash(t_parser *parser)
{
	int		i;
	char	*tmp;

	i = 0;
	while (parser->paths[i])
	{
		tmp = ft_strjoin(parser->paths[i], "/");
		free(parser->paths[i]);
		parser->paths[i] = tmp;
		i++;
	}
}

void	find_paths(t_parser *parser)
{
	t_env	*tmp;
	char	*t;

	tmp = parser->env;
	while (tmp != 0)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			break ;
		tmp = tmp->next;
	}
	if (!(tmp))
		return ;
	t = ft_strdup(tmp->val);
	parser->paths = ft_split(t, ':');
	add_slash(parser);
	free(t);
}
