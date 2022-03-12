/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 20:05:23 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/02 20:56:50 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = (char *)haystack;
	s2 = (char *)needle;
	j = ft_strlen(s2);
	if (s2[i] == '\0')
		return ((char *)haystack);
	while (s1[i] != '\0' && i < len)
	{
		if (s1[i] == s2[0] && i + j <= len)
		{
			if (ft_strncmp(&s1[i], s2, j) == 0)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (0);
}
