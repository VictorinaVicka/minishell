/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsplitter3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 00:56:35 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/03 01:26:13 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_ms(t_ms **alst, t_ms *new)
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
	if (new->separator == 0 && ft_strchr(new->content, '*') != NULL)
		buffer->next = ft_parse_wildcard(new, ft_strchr(new->content, '*'));
	else
		buffer->next = new;
}

t_ms	*ft_parse_wildcard(t_ms *new, char *b)
{
	char *b_end;
	char *check;

	if (b == NULL)
		return (new);
	b_end = b;
	while (*b_end == '*')
		b_end++;
	b_end = ft_strdup(b_end);
	*b = 0;
	check = ft_ls(new->content, b_end);
	free(b_end);
	*b = '*';
	if (check != NULL)
	{
		free(new->content);
		free(new);
		new = ft_lstsplit_ms(check);
		new->space = 1;
		free(check);
	}
	return (new);
}
