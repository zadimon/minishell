/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:01:17 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/05 21:17:36 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	sym;
	unsigned char	*cdst;
	unsigned char	*csrc;

	i = 0;
	sym = (unsigned char)c;
	cdst = dst;
	csrc = (unsigned char *)src;
	while (i < n)
	{
		cdst[i] = csrc[i];
		if (csrc[i] == sym)
			return (&dst[i + 1]);
		i++;
	}
	return (0);
}
