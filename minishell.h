/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:33:50 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/03/10 19:27:05 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>

void	parser(char *s);
char	*start_parser(char *s);
char	*away_sin_quo(char *s, int *i);
char	*away_slash(char *s, int *i);
char	*away_dou_quo(char *s, int *i);
char	*ft_threestrcat(char *s1, char *s2, char *s3);
int		preparser(char *c);
int		put_sytax_error(char c);
int		put_sytax_error_str(char c);
int		check_close_quotes(char *s, int *i);
int		check_sin_quotes(char *s, int *i);
int		check_dou_quotes(char *s, int *i);

#endif
