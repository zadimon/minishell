/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:39:03 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/04/12 13:59:52 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_readline(t_parser *parser)
{
	char	*str;

	signal(SIGINT, restore_prompt);
	signal(SIGQUIT, SIG_IGN);
	rl_on_new_line();
	str = readline("\033[1m\033[149;33mminishell>\033[0m ");
	if (str && !*str)
	{
		free(str);
		return ;
	}
	if (!(str))
	{
		printf("\033[1m\033[149;33mminishell>\033[0m exit\n");
		exit(0);
	}
	add_history(str);
	parsing(str, parser);
}

int	main(int argc, char **argv, char **envp)
{
	t_parser	parser;

	(void)argv;
	parser.exit_code = 0;
	parser.env = env_to_envlst(envp);
	if (argc > 1)
		exit (1);
	while (1)
		start_readline(&parser);
	free_envlst(parser.env);
	return (0);
}
