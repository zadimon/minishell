/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 23:13:15 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/11 16:34:21 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	put_error(void)
{
	ft_putstr_fd("minishel: ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int	put_open_error(char *file_name, char *amb, int error)
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
	if (is_directory(file_name))
		ft_putendl_fd("is a directory", 2);
	else
		ft_putendl_fd(strerror(error), 2);
	return (1);
}

void	put_execve_error(char *cmd, int is_file)
{
	if (ft_strchr(cmd, '/') || is_file == 1)
	{
		ft_putstr_fd("minishel: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		if (is_directory(cmd))
		{
			ft_putendl_fd("is a directory", 2);
			exit(EXIT_IS_A_DIR);
		}
		else
		{
			ft_putendl_fd(strerror(errno), 2);
			exit(EXIT_CMD_NOT_FOUND);
		}
	}
	else
	{
		ft_putstr_fd("minishel: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd("command not found", 2);
		exit(EXIT_CMD_NOT_FOUND);
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
