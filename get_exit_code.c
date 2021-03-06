/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:58:53 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/11 16:06:04 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_code(int status, t_parser *parser)
{
	if (WIFEXITED(status))
		parser->exit_code = WEXITSTATUS(status);
	else
		parser->exit_code = EXIT_CHILD_INT;
}
