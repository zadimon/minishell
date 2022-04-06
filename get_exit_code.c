/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:58:53 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/06 01:40:33 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_code(t_cmd *cmd, int status, int w_case, t_parser *parser)
{
	(void)cmd;
	(void)w_case;
	if (WIFEXITED(status))
		parser->exit_code = WEXITSTATUS(status);
}
