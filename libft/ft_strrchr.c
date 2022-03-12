/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 18:25:59 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/02 20:15:55 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			n;
	unsigned char	sym;

	n = ft_strlen(s);
	sym = (unsigned char) c;
	while (n > 0)
	{
		if (s[n] == sym)
			return ((char *)(s + n));
		n--;
	}
	if (s[0] == sym)
		return ((char *)(s + 0));
	return (0);
}
