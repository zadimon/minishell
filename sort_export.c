/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmother <lmother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:05:18 by lmother           #+#    #+#             */
/*   Updated: 2022/03/12 16:44:46 by lmother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_unsort_node(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->flag == -1)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	get_next_index(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->flag == 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	init_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		tmp->index = 0;
		tmp->flag = -1;
		tmp = tmp->next;
	}
}

static int	get_min(t_env *env)
{
	t_env	*tmp;
	t_env	*node;

	tmp = find_unsort_node(env);
	if (!tmp)
		return (1);
	tmp->flag = 0;
	node = tmp->next;
	while (node)
	{
		if (tmp->key[0] > node->key[0] && node->flag == -1)
		{
			tmp->flag = -1;
			tmp = node;
			node->flag = 0;
		}
		node = node->next;
	}
	tmp->index = get_next_index(env);
	return (0);
}

int	sort_export(t_env *env, int size)
{
	int	i;

	i = 0;
	init_env(env);
	while (i < size)
	{
		get_min(env);
		i++;
	}
	return (0);
}
