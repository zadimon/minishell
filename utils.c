/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmother <lmother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:11:56 by lmother           #+#    #+#             */
/*   Updated: 2022/03/12 16:44:52 by lmother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_error(char *s1, int errnum, char *msg, char *s2)
{
	char	*errmes;

	if (s1)
	{
		if (!msg)
			errmes = strerror(errnum);
		else
			errmes = msg;
		write(2, "minishell: ", 12);
		write(2, s1, ft_strlen(s1));
		if (s2)
		{
			write(2, ": ", 3);
			if (!errnum)
				write(2, "`", 1);
			write(2, s2, ft_strlen(s2));
			if (!errnum)
				write(2, "'", 1);
		}
		write(2, ": ", 3);
		write(2, errmes, ft_strlen(errmes));
		write(2, "\n", 1);
	}
	return (1);
}

void	free_envlst(t_env *lst)
{
	t_env	*tmp;
	t_env	*node;

	tmp = lst;
	node = NULL;
	while (tmp)
	{
		node = tmp->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
		tmp = node;
	}
}

int	get_size_envp(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/*how many arguments*/
int	num_of_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}
