/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:45:46 by lmother           #+#    #+#             */
/*   Updated: 2022/04/08 18:58:22 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_lstlast(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (tmp != NULL)
	{
		while (tmp->next != 0)
			tmp = tmp->next;
	}
	return (tmp);
}

int	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->val)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}

int	env(char **argv, t_env *env)
{
	if (!num_of_args(argv))
		return (print_env(env));
	else
		return (p_error("env", 2, NULL, argv[0]));
}
