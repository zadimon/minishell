/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:34:15 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/11 23:25:12 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	iter_shlvl(t_env *env)
{
	t_env	*tmp;
	int		num;

	tmp = env;
	num = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "SHLVL"))
		{
			num = ft_atoi(tmp->val);
			num++;
			free(tmp->val);
			tmp->val = ft_itoa(num);
			break ;
		}
		tmp = tmp->next;
	}
}

void	shlvl(char	*str, t_env *env)
{
	char	*res;

	res = ft_strnstr(str, "minishell", ft_strlen(str));
	while (res)
	{
		if (!ft_strcmp(res, "minishell"))
		{
			if (access(str, X_OK) == 0)
			{
				iter_shlvl(env);
				break ;
			}
		}
		res = res + 1;
		res = ft_strnstr(res, "minishell", ft_strlen(str));
	}
}
