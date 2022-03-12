/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:31:51 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/11 18:27:27 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_iterative_power(size_t nb, size_t power)
{
	size_t	i;

	i = 1;
	while (power > 0)
	{
		i = nb * i;
		power--;
	}
	return (i);
}

static int	ft_isspace(int c)
{
	unsigned char	sym;

	sym = (unsigned char)c;
	if (sym == ' ' || sym == '\t' || sym == '\n'
		|| sym == '\v' || sym == '\f' || sym == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	size_t	num;
	size_t	i;
	int		minus;

	num = 0;
	i = 0;
	minus = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (num != 0 && num >= ft_iterative_power(2, (sizeof(size_t) * 8) - 1)
		&& minus == -1)
		return (0);
	if (num != 0 && num >= ft_iterative_power(2, (sizeof(size_t) * 8) - 1) - 1
		&& minus == 1)
		return (-1);
	return (((int)num) * minus);
}
