/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:29:19 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/03 01:28:15 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_item(char ***as)
{
	if (as != NULL && *as != NULL && **as != NULL)
	{
		free(**as);
		**as = NULL;
	}
}

void	free_flux(t_terminal *terminal)
{
	t_thread *begin;
	t_thread *current;

	begin = terminal->thread;
	while (terminal->thread->next)
	{
		current = terminal->thread->next;
		free(terminal->thread->next->file);
		free(terminal->thread->next);
		terminal->thread->next = NULL;
		terminal->thread->next = current->next;
	}
	terminal->thread = begin;
	if (terminal->buf)
		free(terminal->buf);
	terminal->buf = NULL;
	if (terminal->pipes)
		free(terminal->pipes);
}

void	free_double_tab(char ***item, int i)
{
	int j;

	if (item && item[i] && *item[i])
	{
		j = 0;
		while (item[i][j])
		{
			ft_strdel(&item[i][j]);
			j++;
		}
		free(item[i][j]);
		free(item[i]);
		item[i] = NULL;
	}
}
