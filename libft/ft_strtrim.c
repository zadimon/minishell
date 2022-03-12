/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 19:48:42 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/12 13:46:57 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *set, int c)
{
	size_t	i;

	i = 0;
	while (set[i] != c && set[i] != '\0')
		i++;
	if (set[i] != '\0')
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (s1 == 0 || set == 0)
		return (0);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] != '\0' && ft_isset(set, s1[i]))
		i++;
	while (j > 0 && ft_isset(set, s1[j]))
		j--;
	if (s1[i] == '\0')
		return (ft_substr(s1, 0, 0));
	str = ft_substr(s1, i, j + 1 - i);
	return (str);
}
