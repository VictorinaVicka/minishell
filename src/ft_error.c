/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 23:19:45 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:10:02 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_terminal *terminal, int j)
{
	t_environment	*begin;

	begin = terminal->lst_env;
	while (terminal->lst_env)
	{
		if (!ft_strncmp(terminal->lst_env->name, "?", 2))
		{
			free(terminal->lst_env->value);
			terminal->lst_env->value = ft_itoa(j);
		}
		terminal->lst_env = terminal->lst_env->next;
	}
	terminal->lst_env = begin;
}

void	ft_error_message(t_terminal *terminal)
{
	ft_error(terminal, 1);
	ft_printf("%s: %s: %s:\n", terminal->cmds_pipe[terminal->nb_pipe],
	terminal->split_pipe[terminal->nb_pipe], strerror(errno));
	exit(0);
}

void	test_path(t_terminal *terminal, int i)
{
	i = 0;
	if (!ft_strncmp(terminal->tab_path[terminal->nb_pipe][i],
	terminal->cmds_pipe
		[terminal->nb_pipe], 3))
	{
		ft_printf("%s: no such file or directory\n",
		terminal->cmds_pipe[terminal->nb_pipe]);
		exit(127);
	}
}

void	test_path_null(t_terminal *terminal, int i)
{
	if (terminal->tab_path[terminal->nb_pipe][i] == NULL)
	{
		ft_printf("%s: command not found\n",
		terminal->cmds_pipe[terminal->nb_pipe]);
		exit(127);
	}
}
