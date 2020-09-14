/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 00:47:48 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/03 01:25:38 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms		*ft_lstnew_ms(const void *content, char separator, int flag)
{
	t_ms			*buffer;

	if (!(buffer = (t_ms*)malloc(sizeof(t_ms))))
		return (NULL);
	if (!content)
		content = NULL;
	else
		buffer->content = (void*)content;
	if (separator == 34 && (!(flag & 4) && !(flag & 2)))
		buffer->separator = 1;
	else if (separator == 39 && (!(flag & 4) && !(flag & 2)))
		buffer->separator = 2;
	else
		buffer->separator = 0;
	if (flag != 8)
		buffer->space = 0;
	buffer->next = NULL;
	return (buffer);
}

void		ft_lstadd_back_ms_ls(t_ms **alst, t_ms *new)
{
	t_ms	*buffer;

	if (alst == NULL)
		return ;
	buffer = *alst;
	if (new == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (buffer->next != NULL)
		buffer = buffer->next;
}

void		ft_lstclear_ms(t_ms **lst, void (*del)(void*))
{
	t_ms	*buffer;
	t_ms	*buffernext;

	if (!(*del))
		return ;
	if (lst == NULL)
		return ;
	buffer = *lst;
	while (buffer != NULL)
	{
		buffernext = buffer->next;
		del(buffer->content);
		free(buffer);
		buffer = buffernext;
	}
	free(buffer);
	*lst = NULL;
}

int			ft_lstsize_ms(t_ms *lst)
{
	t_ms	*buffer;
	int		size;

	size = 0;
	if (lst == NULL)
		return (0);
	buffer = lst;
	while (buffer != NULL)
	{
		buffer = buffer->next;
		size++;
	}
	return (size);
}

void		ft_print_lst(t_ms *lst)
{
	while (lst)
	{
		ft_printf("-------\n");
		ft_printf("Content: %s\nseparator: %d\n", lst->content, lst->separator);
		ft_printf("Space: %d\n", lst->space);
		lst = lst->next;
	}
	ft_printf("----------------\n");
}
