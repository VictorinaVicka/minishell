/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 01:36:44 by qsymond           #+#    #+#             */
/*   Updated: 2020/08/31 01:46:28 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		add_garbage(t_terminal *terminal, void **s)
{
	ft_lstadd_front(&terminal->gb_collector2, ft_lstnew(*s));
}

void		free_cmds(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i] != 0)
		free(cmds[i++]);
	free(cmds);
}

void		do_safe_exit(t_terminal *terminal)
{
	if (terminal->cmds)
		free_cmds(terminal->cmds);
	ft_lstclear(&terminal->gb_collector2, free);
	exit(0);
}

void		*add_garbage_ret(t_terminal *terminal, void **s)
{
	t_list *b;

	if (!(b = malloc(sizeof(t_list))))
		do_safe_exit(terminal);
	if (*s)
		b->content = *s;
	else
		b->content = NULL;
	b->next = NULL;
	if (*s)
		ft_lstadd_front(&terminal->gb_collector2, b);
	return (*s);
}
