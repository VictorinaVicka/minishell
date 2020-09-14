/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:57:33 by qsymond           #+#    #+#             */
/*   Updated: 2020/08/31 01:47:15 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_terminal(t_terminal *terminal)
{
	terminal->n_cmds = 0;
	terminal->i = 0;
	terminal->cmds = NULL;
	free(terminal->sep);
	terminal->sep = NULL;
	terminal->lst = NULL;
	terminal->buf = NULL;
	terminal->code = 0;
	ft_memset(terminal->pipe, 0, sizeof(terminal->pipe));
	terminal->cmd_pipe = 0;
	terminal->pipes = NULL;
	terminal->tab_path = NULL;
	terminal->cmds_pipe = NULL;
	terminal->args_pipe = NULL;
	terminal->split_pipe = NULL;
	terminal->first = 1;
	terminal->thread->redirect = 'z';
	free(terminal->entry);
	terminal->entry = NULL;
	terminal->option_n = 0;
	terminal->gb_collector2 = NULL;
}

void	ft_free_lst(t_ms **lst)
{
	int i;

	i = 0;
	while (lst[i] != 0)
	{
		ft_lstclear_ms(&lst[i], free);
		i++;
	}
	free(lst[i]);
	free(lst);
}

void	clear_memory(t_terminal *terminal)
{
	ft_free_lst(terminal->lst);
	ft_clearlist(terminal->cmds);
	ft_lstclear(&terminal->gb_collector2, free);
	clear_terminal(terminal);
}
