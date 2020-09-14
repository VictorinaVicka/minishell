/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_chev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 01:42:54 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/03 01:26:26 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms	*ft_lstnew_chev(char **s)
{
	t_ms			*buffer;

	if (!(buffer = (t_ms*)malloc(sizeof(t_ms))))
		return (NULL);
	buffer->content = (void*)*s;
	buffer->separator = 0;
	buffer->space = 0;
	buffer->next = NULL;
	return (buffer);
}

void		ft_lst_insert_one_ms(t_ms *lst, t_ms *new)
{
	t_ms *b;

	b = lst->next;
	lst->next = new;
	new->next = b;
}

static t_ms	*ft_parse_chev_2(char *b, int i, int j, t_ms *lst)
{
	char	*b_chev;
	char	*b_cont;

	b_chev = ft_strndup(&b[i], j - i);
	b_cont = ft_strdup(&b[j]);
	free(lst->content);
	if (i != 0)
	{
		lst->content = ft_strndup(b, i);
		ft_lst_insert_one_ms(lst, ft_lstnew_chev(&b_chev));
		lst = lst->next;
		if (b_cont[0] != 0)
			ft_lst_insert_one_ms(lst, ft_lstnew_chev(&b_cont));
	}
	else
	{
		lst->content = b_chev;
		if (b_cont[0] != 0)
			ft_lst_insert_one_ms(lst, ft_lstnew_chev(&b_cont));
		lst = lst->next;
	}
	if (b_cont[0] == 0)
		free(b_cont);
	return (lst);
}

static t_ms	*ft_parse_chev_3(t_ms *lst, char *b)
{
	int	i;
	int	j;

	i = 0;
	while (lst && lst->separator == 0 && b[i] != 0)
	{
		if (b[i] == '>')
		{
			j = i;
			while (b[j] == '>')
				j++;
			lst = ft_parse_chev_2(b, i, j, lst);
			break ;
		}
		else if (b[i] == '<')
		{
			j = i;
			while (b[j] == '<')
				j++;
			lst = ft_parse_chev_2(b, i, j, lst);
			break ;
		}
		i++;
	}
	return (lst);
}

void		ft_parse_chev(t_ms *lst)
{
	char	*b;
	int		i;

	while (lst)
	{
		i = 0;
		b = (char*)lst->content;
		ft_parse_chev_3(lst, b);
		if (lst)
			lst = lst->next;
	}
}
