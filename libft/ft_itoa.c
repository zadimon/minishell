/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:15:08 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/11 19:00:41 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numcount(int n)
{
	int	count;

	count = 1;
	if (n > 0)
		count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		count;
	int		neg;

	neg = 1;
	count = ft_numcount(n);
	if (n < 0)
		neg = -1;
	num = malloc(sizeof(*num) * (count + 1));
	if (!(num))
		return (0);
	num[count] = '\0';
	while (count - 1 >= 0)
	{
		num[count - 1] = neg * (n % 10) + '0';
		n /= 10;
		count--;
	}
	if (neg == -1)
		num[0] = '-';
	return (num);
}
