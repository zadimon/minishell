/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 16:13:33 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/02 18:23:39 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*src;
	unsigned char	sym;

	i = 0;
	src = (unsigned char *)s;
	sym = c;
	while (i < n)
	{
		if (src[i] == sym)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
