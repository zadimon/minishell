/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebhakaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 21:17:58 by ebhakaz           #+#    #+#             */
/*   Updated: 2021/05/06 13:27:04 by ebhakaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*buf;
	t_list	*new;
	int		i;

	i = 1;
	tmp = lst;
	while (tmp != 0)
	{
		new = ft_lstnew(f(tmp->content));
		if (!(new))
		{
			ft_lstclear(&new, del);
			return (0);
		}
		if (i == 1)
		{
			buf = new;
			i = 0;
		}
		else
			ft_lstadd_back(&buf, new);
		tmp = tmp->next;
	}
	return (buf);
}
