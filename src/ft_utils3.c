/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 01:18:35 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/03 01:28:12 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_terminal *terminal)
{
	ft_delete_space(terminal->buf);
	write_redir(terminal);
	exit(0);
}

int		test_builtin(t_terminal *terminal)
{
	char *str;

	str = ft_strdup(terminal->cmds_pipe[terminal->nb_pipe]);
	if (ft_strncmp(str, "unset", 6) == 0 || ft_strncmp(str, "exit", 5) ==
		0 || ft_strncmp(str, "cd", 3) == 0 ||
		(ft_strncmp(str, "export", 7) == 0 && terminal->no_arg == 0))
	{
		terminal->buf = ft_strdup("");
		terminal->option_n = 1;
		free(str);
		ft_echo(terminal);
		return (1);
	}
	else if (ft_strncmp(terminal->cmds_pipe[terminal->nb_pipe], "echo", 5) == 0)
	{
		free(str);
		ft_echo(terminal);
	}
	free(str);
	return (0);
}

int		ft_close(t_terminal *terminal, int nb)
{
	close(terminal->pipes[nb][0]);
	close(terminal->pipes[nb][1]);
	return (0);
}

void	ft_lstadd_back_flux(t_thread **alst, t_thread *new)
{
	t_thread *tmp;

	if (alst && new)
	{
		tmp = *alst;
		if (!(*alst))
		{
			*alst = new;
			return ;
		}
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	return ;
}
