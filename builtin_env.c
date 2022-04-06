/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:54:29 by lmother           #+#    #+#             */
/*   Updated: 2022/04/05 23:01:03 by ebhakaz          ###   ########.fr       */
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
	char	*spec_sym;
	char	*tmp;

	tmp = content;
	newlst = malloc(sizeof(t_env));
	if (!newlst)
		return (NULL);
	spec_sym = ft_strchr(tmp, '=');
	if (spec_sym)
	{
		*spec_sym = '\0';
		newlst->key = ft_strdup(tmp);
		newlst->val = ft_strdup(++spec_sym);
		newlst->next = NULL;
	}
	else if (tmp)
	{
		newlst->key = ft_strdup(tmp);
		newlst->val = NULL;
		newlst->next = NULL;
	}
	return (newlst);
}
/*add node to env list from envp*/

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
		{
			new = env_lstlast(new);
			new->next = env_lstnew(envp[i]);
			if (!new->next)
				return (NULL);
		}
	}
	return (head);
}
