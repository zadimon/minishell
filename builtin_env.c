/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:54:29 by lmother           #+#    #+#             */
/*   Updated: 2022/04/08 18:31:27 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	edit_key(t_env *tmp, char *val)
{
	if (val)
		++val;
	if (tmp && tmp->val)
		free(tmp->val);
	if (tmp)
		tmp->val = ft_strdup(val);
	if (val)
		--val;
}

int	findkey_env(t_env *env, char *key, int edit)
{
	t_env	*tmp;
	char	*spec;

	tmp = env;
	spec = ft_strrchr(key, '=');
	if (spec)
		*spec = '\0';
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (edit == 1)
				edit_key(tmp, spec);
			if (spec)
				*spec = '=';
			return (0);
		}
		tmp = tmp->next;
	}
	if (spec)
		*spec = '=';
	return (1);
}

/* new node to env_lst*/
t_env	*env_lstnew(char *content)
{
	t_env	*newlst;
	int		i;

	newlst = malloc(sizeof(t_env));
	if (!newlst)
		return (NULL);
	i = 0;
	while (content[i] != '=' && content[i] != '\0')
		i++;
	if (content[i] == '=')
	{
		newlst->key = ft_substr(content, 0, i);
		newlst->val = ft_strdup(content + i + 1);
		newlst->next = NULL;
	}
	else
	{
		newlst->key = ft_strdup(content);
		newlst->val = NULL;
		newlst->next = NULL;
	}
	return (newlst);
}
/*add node to env list from envp*/

static t_env	*add_back(t_env *new, char *str)
{
	new = env_lstlast(new);
	new->next = env_lstnew(str);
	if (!new->next)
		return (NULL);
	return (new);
}

t_env	*env_to_envlst(char **envp)
{
	t_env	*new;
	t_env	*head;
	int		i;

	i = -1;
	new = NULL;
	head = NULL;
	while (envp[++i])
	{
		if (!new)
		{
			new = env_lstnew(envp[i]);
			head = new;
			if (!new)
				return (NULL);
		}
		else
			new = add_back(new, envp[i]);
	}
	return (head);
}
