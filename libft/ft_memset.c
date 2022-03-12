/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 19:19:34 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/02 17:14:02 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	sym;
	unsigned char	*mas;

	i = 0;
	sym = (unsigned char)c;
	mas = b;
	while (i < len)
	{
		mas[i] = sym;
		i++;
	}
	return (b);
}
