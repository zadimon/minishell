/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:13:15 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/07 05:06:26 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_error(void)
{
	ft_putstr_fd("minishel: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int	put_open_error(char *file_name, char *amb)
{
	if (file_name[0] == '\0')
	{
		ft_putstr_fd("minishel: ", 2);
		ft_putstr_fd(amb, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("ambiguous redirect", 2);
		return (1);
	}
	ft_putstr_fd("minishel: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

void	put_execve_error(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		put_open_error(cmd, 0);
	else
	{
		ft_putstr_fd("minishel: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("command not found", 2);
	}
}

int	ft_close(int fd, char *file_name)
{
	if (fd > 0)
	{
		if (close(fd) == -1)
		{
			ft_putstr_fd("minishel: ", 2);
			ft_putstr_fd(file_name, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return (1);
		}
	}
	return (0);
}
