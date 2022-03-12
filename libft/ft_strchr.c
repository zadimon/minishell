/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:10:33 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/02 20:13:49 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	size_t			n;
	unsigned char	sym;

	i = 0;
	n = ft_strlen(s);
	sym = (unsigned char) c;
	while (i < n)
	{
		if (s[i] == sym)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == sym)
		return ((char *)(s + i));
	return (0);
}
