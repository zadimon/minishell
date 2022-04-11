/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:20:21 by lmother           #+#    #+#             */
/*   Updated: 2022/04/08 22:13:22 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_pwd_oldpw(t_env *env, char *key, char *val)
{
	t_env	*newlst;
	t_env	*tmp;
	t_env	*last;

	tmp = env;
	last = env_lstlast(env);
	newlst = malloc(sizeof(t_env));
	if (!newlst)
		return (1);
	if (tmp != NULL && tmp->next)
	{
		while (tmp->next->next != NULL)
			tmp = tmp->next;
	}
	newlst->key = ft_strdup(key);
	newlst->val = ft_strdup(val);
	newlst->next = last;
	tmp->next = newlst;
	return (0);
}

/*change key in env_lst*/
int	change_key(t_env *env, char *key, char *val)
{
	t_env	*tmp;

	tmp = env;
	if (!findkey_env(env, key, 0))
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, key))
			{
				free(tmp->val);
				tmp->val = ft_strdup(val);
				return (0);
			}
			tmp = tmp->next;
		}
	}
	if (!ft_strcmp("PWD", key))
		add_pwd_oldpw(env, key, val);
	if (!ft_strcmp("OLDPWD", key))
		add_pwd_oldpw(env, key, val);
	return (1);
}

int	ch_dir_try(char	*path, t_env *env)
{
	change_key(env, "OLDPWD", getcwd(NULL, 0));
	if (!chdir(path))
		return (change_key(env, "PWD", getcwd(NULL, 0)));
	else
		return (p_error("cd", errno, NULL, path));
	return (1);
}

int	ch_dir(char *path, t_env *env)
{
	char	*val;
	int		res;

	val = ft_strdup(get_valenv("OLDPWD", env));
	res = 0;
	if (!ft_strcmp(path, "~"))
	{
		if (!ch_dir_try("/Users/lmother", env)
			|| !ch_dir_try("/Users/ebhakaz", env))
			return (0);
	}
	if (!ft_strcmp(path, "-"))
	{
		if (val && !findkey_env(env, "OLDPWD", 0))
		{
			res = ch_dir_try(val, env);
			free(val);
			return (res);
		}
		else
			return (p_error("cd", 0, "OLDPWD not set", NULL));
	}
	return (ch_dir_try(path, env));
}

int	cd(char **args, t_env *env)
{
	char	*key;

	key = get_valenv("HOME", env);
	if (!num_of_args(args))
	{
		if (!key)
			return (p_error("cd", 0, "HOME not set", NULL));
		else
			return (ch_dir(key, env));
	}
	else
		return (ch_dir(args[0], env));
	return (1);
}
