/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:44:26 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/10 18:47:11 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *h;
	t_list *tmp;
	t_list *new;

	h = NULL;
	if (lst && f)
	{
		tmp = lst;
		if ((h = ft_lstnew(f(tmp->content))) == 0)
			return (0);
		tmp = tmp->next;
		while (tmp)
		{
			if (!(new = ft_lstnew(f(tmp->content))))
			{
				ft_lstclear(&h, del);
				h = NULL;
				break ;
			}
			ft_lstadd_back(&h, new);
			tmp = tmp->next;
		}
	}
	return (h);
}
