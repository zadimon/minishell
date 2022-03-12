/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:33:31 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/03/10 20:29:53 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*s;

	(void)envp;
	(void)argc;
	(void)argv;
	s = ft_strdup("\\''l\\s -l'\\'a \\ \"libft\\\"\"");
	printf("before %s\n", s);
	parser(s);
	s = ft_strdup("\"\\\"\"||");
	printf("before %s\n", s);
	parser(s);
	s = ft_strdup("'||'a''");
	printf("before %s\n", s);
	parser(s);
	return (0);
}
