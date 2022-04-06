/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmother <lmother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:07:42 by lmother           #+#    #+#             */
/*   Updated: 2022/03/12 16:43:25 by lmother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

int	echo(char *option, char **args)
{
	int	i;

	i = 1;
	if (option && option[0] == '-')
	{
		while (option[++i])
		{
			if (option[i] != 'n')
			{
				print_args(args);
				write(1, "\n", 1);
				return (1);
			}
		}
		print_args(++args);
		return (0);
	}
	print_args(args);
	write(1, "\n", 1);
	return (0);
}
