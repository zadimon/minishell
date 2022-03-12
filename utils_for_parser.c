/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:25:33 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/03/10 19:26:42 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_sytax_error_str(char c)
{
	printf("minishell: syntax error near unexpected token `%c%c'\n", c, c);
	return (1);
}

int	put_sytax_error(char c)
{
	printf("minishell: syntax error near unexpected token `%c'\n", c);
	return (1);
}

char	*ft_threestrcat(char *s1, char *s2, char *s3)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	s1 = ft_strdup(res);
	free(res);
	res = ft_strjoin(s1, s3);
	free(s1);
	free(s2);
	free(s3);
	return (res);
}
