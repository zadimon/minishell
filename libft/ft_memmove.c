/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 13:56:44 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/02 17:16:01 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!(dst) && !(src))
		return (0);
	if (dst <= src)
	{
		while (i < len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else
	{	
		while (len > 0)
		{
			*(unsigned char *)(dst + len - 1) = *(unsigned char *)
				(src + len - 1);
			len--;
		}
	}
	return (dst);
}
