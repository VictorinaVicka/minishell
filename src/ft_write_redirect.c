/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 23:54:07 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/03 01:28:25 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		write_redir(t_terminal *terminal)
{
	t_thread *begin_thread;

	begin_thread = terminal->thread;
	while (terminal->thread != 0)
	{
		if (!terminal->option_n)
			dprintf(1, "%s\n", terminal->buf);
		else
			dprintf(1, "%s", terminal->buf);
		if (terminal->thread->next != NULL)
			terminal->thread = terminal->thread->next;
		else
			break ;
	}
	terminal->thread = begin_thread;
	return (1);
}
