/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_av.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:36:14 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:56:29 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ms	*parse_av2(t_terminal *trm, t_ms *lst, int *i, char **av)
{
	if (*i == 0 || lst->space == 1)
	{
		av[*i] = ft_strdup(ft_write_args(trm, lst->content, 0));
		lst = lst->next;
		*i += 1;
		av[*i] = 0;
	}
	else if (lst != NULL && lst->space == 0)
	{
		while (lst != NULL && lst->space == 0 &&
		(ft_strncmp(lst->content, ">", 1) && ft_strncmp(lst->content, "<", 1)))
		{
			av[*i] = ft_shelljoin(av[*i], ft_write_args(trm, lst->content, 0));
			lst = lst->next;
		}
		if (lst && ft_strncmp(lst->content, ">", 1) &&
		ft_strncmp(lst->content, "<", 1))
		{
			av[*i] = ft_shelljoin(av[*i], ft_write_args(trm, lst->content, 0));
			lst = lst->next;
		}
		*i += 1;
	}
	return (lst);
}

static int	ft_count_chev(t_ms *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		if ((!ft_strncmp(lst->content, ">", 1) ||
		(!ft_strncmp(lst->content, "<", 1))) && lst->separator == 0)
		{
			lst = lst->next;
			size++;
			if (lst != NULL)
			{
				size++;
				lst = lst->next;
			}
			continue ;
		}
		lst = lst->next;
	}
	return (size);
}

char		**parse_av(t_terminal *terminal, t_ms *lst)
{
	char	**av;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize_ms(lst) - ft_count_chev(lst);
	if (!(av = malloc((size + 1) * sizeof(char*))))
		return (NULL);
	while (i < size && lst)
	{
		if ((!ft_strncmp(lst->content, ">", 1) ||
		(!ft_strncmp(lst->content, "<", 1))) && lst->separator == 0)
		{
			lst = lst->next;
			if (lst != NULL)
				lst = lst->next;
			continue ;
		}
		lst = parse_av2(terminal, lst, &i, av);
	}
	av[i] = 0;
	return (av);
}
