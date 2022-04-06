/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmother <lmother@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:24:51 by lmother           #+#    #+#             */
/*   Updated: 2022/03/12 16:43:40 by lmother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	p_error_exit(char *s1, int errnum, char *msg, char *s2)
{
	char	*errmes;

	if (s1)
	{
		if (!msg)
			errmes = strerror(errnum);
		else
			errmes = msg;
		write(2, s1, ft_strlen(s1));
		if (s2)
		{
			write(2, ": ", 3);
			write(2, s2, ft_strlen(s2));
		}
		write(2, ": ", 3);
		write(2, errmes, ft_strlen(errmes));
		write(2, "\n", 1);
	}
	return (1);
}

static int	check_digit(char *argv)
{
	int	i;
	int	minus;

	i = -1;
	minus = 0;
	while (argv[++i])
	{
		if (argv[i] == '-')
		{
			minus = 1;
			continue ;
		}
		if ((i - minus) > 19)
		{
			write(1, "exit\n", 5);
			p_error_exit("exit", 0, "numeric argument required", argv);
			exit (-1);
		}
	}
	return (0);
}

int	check_argv_exit(char *argv)
{
	int	i;

	i = -1;
	while (argv && argv[++i])
	{
		if (argv[i] == '-' && !argv[i + 1] && i == 0)
		{
			write(1, "exit\n", 5);
			return (p_error_exit("exit", 0, "numeric argument required", argv));
		}
		if (argv[i] == '-' && i == 0)
			i++;
		if (argv[i] < '0' || argv[i] > '9')
		{
			write(1, "exit\n", 5);
			return (p_error_exit("exit", 0, "numeric argument required", argv));
		}
	}
	return (0);
}

int	ft_exit(char **argv, t_env *env)
{
	(void)env;
	if (num_of_args(argv) > 0)
	{
		if (check_argv_exit(argv[0]))
			exit (-1);
		else if (num_of_args(argv) == 1)
		{
			check_digit(argv[0]);
			write(1, "exit\n", 5);
			exit (ft_atoi(argv[0]));
		}
		else
		{
			write(1, "exit\n", 5);
			return (p_error_exit("exit", 0, "too many arguments", NULL));
		}
	}
	else
	{
		write(1, "exit\n", 5);
		exit (errno);
	}
}
