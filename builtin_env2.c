/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:44:03 by lmother           #+#    #+#             */
/*   Updated: 2022/04/08 19:54:23 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**cat_key_and_val(t_env *env, char **res)
{
	int		i;
	t_env	*tmp;
	char	*str;

	i = -1;
	tmp = env;
	while (tmp)
	{
		res[++i] = ft_strdup(tmp->key);
		str = ft_strdup(res[i]);
		free(res[i]);
		res[i] = ft_strjoin(str, "=");
		free(str);
		str = ft_strdup(res[i]);
		free(res[i]);
		res[i] = ft_strjoin(str, tmp->val);
		free(str);
		tmp = tmp->next;
	}
	res[++i] = 0;
	return (res);
}

char	**new_envp(t_env *env)
{
	int		i;
	char	**res;

	i = get_size_envp(env);
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	return (cat_key_and_val(env, res));
}
