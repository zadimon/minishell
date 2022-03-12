/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 13:35:22 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/06 18:57:23 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_getsize(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[i] != '\0')
	{
		if (i != 0 && s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_getlen(char const *s, char c)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static size_t	ft_getstart(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

static void	ft_free(char **str, size_t k)
{
	size_t	i;

	i = 0;
	while (i <= k)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	k;

	if (!(s))
		return (0);
	str = malloc(sizeof(char **) * (ft_getsize(s, c) + 1));
	if (!(str))
		return (0);
	i = 0;
	k = 0;
	while (k < ft_getsize(s, c))
	{
		i = i + ft_getstart(&s[i], c);
		str[k] = ft_substr(s, i, ft_getlen(&s[i], c));
		i = i + ft_getlen(&s[i], c);
		if (!(str[k]))
		{
			ft_free(str, k);
			return (0);
		}
		k++;
	}
	str[k] = 0;
	return (str);
}
