/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_syntax_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:10:59 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/03 17:14:18 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_syntax_error_str(char c)
{
	printf("minishell: syntax error near unexpected token `%c%c'\n", c, c);
	return (1);
}

int	put_syntax_error(char c)
{
	printf("minishell: syntax error near unexpected token `%c'\n", c);
	return (1);
}

int	put_syntax_error_newline(char c)
{
	if (c == '\0')
		printf("minishell: syntax error near unexpected token 'newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	return (1);
}
