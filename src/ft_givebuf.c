/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_givebuf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 01:09:16 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:23:52 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms	*get_buffer_utils(t_ms *lst)
{
	lst = lst->next;
	if (lst != NULL)
		lst = lst->next;
	return (lst);
}

char		*get_buffer(t_terminal *d, t_ms *lst)
{
	int		j;
	char	*b;

	j = 0;
	b = ft_strdup("");
	while (lst != NULL)
	{
		if ((!ft_strncmp(lst->content, ">", 1) ||
		!ft_strncmp(lst->content, "<", 1)) && lst->separator == 0)
		{
			lst = get_buffer_utils(lst);
			continue ;
		}
		if (lst->content != NULL)
		{
			b = ft_shelljoin(b, ft_write_args(d, lst->content, lst->separator));
			if (lst->space == 1 && lst->next != NULL &&
			ft_strncmp(ft_write_args(d, lst->next->content,
			lst->next->separator), "", 1) && ft_strncmp(ft_write_args(d,
			lst->content, lst->separator), "", 1))
				b = ft_shelljoin(b, " ");
		}
		lst = lst->next;
	}
	return (add_garbage_ret(d, (void**)&b));
}
