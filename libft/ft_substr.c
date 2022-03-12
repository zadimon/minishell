/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <ebhakaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:10:55 by ebhakaz           #+#    #+#             */
/*   Updated: 2022/02/17 16:57:10 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	min_len;

	if (!(s))
		return (0);
	min_len = ft_strlen(&s[start]);
	if (start >= ft_strlen(s))
		len = 0;
	else if (min_len < len)
		len = min_len;
	str = malloc(sizeof(*str) * (len + 1));
	if (!(str))
		return (0);
	i = 0;
	while (i < len && start + i < ft_strlen(s))
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
