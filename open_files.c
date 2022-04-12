/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 17:42:51 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/12 00:36:38 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile(t_cmd *cmd, t_rd *rd)
{
	if (rd->which_case == INFILE_CASE)
	{
		if (cmd->infile_d > 0)
			ft_close(cmd->infile_d, cmd->infile);
		free(cmd->infile);
		free(cmd->is_amb);
		cmd->infile_d = open(rd->file_name, O_RDONLY);
		cmd->infile = ft_strdup(rd->file_name);
		cmd->is_amb = ft_strdup(rd->is_amb);
	}
	else if (rd->which_case == HEREDOC_CASE)
	{
		if (rd->heredoc_fd > 0)
		{
			if (cmd->infile_d > 0)
				ft_close(cmd->infile_d, cmd->infile);
			free(cmd->infile);
			free(cmd->is_amb);
			cmd->infile_d = rd->heredoc_fd;
			cmd->infile = ft_strdup(rd->file_name);
			cmd->is_amb = ft_strdup(rd->is_amb);
		}
	}
}

void	open_outfile(t_cmd *cmd, t_rd *rd)
{
	if (rd->which_case == OUTFILE_CASE)
	{
		if (cmd->outfile_d > 0)
			ft_close(cmd->outfile_d, cmd->outfile);
		free(cmd->outfile);
		free(cmd->is_amb);
		cmd->outfile_d = open(rd->file_name,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
		cmd->outfile = ft_strdup(rd->file_name);
		cmd->is_amb = ft_strdup(rd->is_amb);
	}
	else if (rd->which_case == APPEND_CASE)
	{
		if (cmd->outfile_d > 0)
			ft_close(cmd->outfile_d, cmd->outfile);
		free(cmd->outfile);
		free(cmd->is_amb);
		cmd->outfile_d = open(rd->file_name,
				O_CREAT | O_RDWR | O_APPEND, 0644);
		cmd->outfile = ft_strdup(rd->file_name);
		cmd->is_amb = ft_strdup(rd->is_amb);
	}
}

void	open_files(t_cmd *cmd)
{
	t_rd	*tmp;

	tmp = cmd->rd;
	while (tmp != 0)
	{
		if (tmp->which_case == INFILE_CASE || tmp->which_case == HEREDOC_CASE)
			open_infile(cmd, tmp);
		else if (tmp->which_case == OUTFILE_CASE
			|| tmp->which_case == APPEND_CASE)
			open_outfile(cmd, tmp);
		if (cmd->infile_d == -1 || cmd->outfile_d == -1)
		{
			cmd->error = errno;
			break ;
		}
		tmp = tmp->next;
	}
}
