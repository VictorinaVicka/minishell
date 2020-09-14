/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 01:20:00 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:09:14 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_terminal *terminal)
{
	char *b;

	b = NULL;
	if (!(b = getcwd(b, 0)))
	{
		ft_printf("Malloc error\n");
		safe_exit(terminal);
	}
	terminal->buf = b;
	write_redir(terminal);
	free(b);
	exit(0);
}

int		ft_fill_env(t_terminal *terminal)
{
	char	*str;
	char	*tmp;

	str = ft_strjoin(terminal->lst_env->name, "=");
	tmp = ft_strjoin(str, terminal->lst_env->value);
	if (terminal->lst_env->next)
		terminal->buf = ft_strjoin(tmp, " ");
	else
		terminal->buf = ft_strdup(tmp);
	free(str);
	free(tmp);
	write_redir(terminal);
	free(terminal->buf);
	terminal->buf = NULL;
	if (terminal->thread->redirect == 'w')
		terminal->thread->redirect = 'a';
	return (0);
}

void	ft_env(t_terminal *terminal, t_ms *lst)
{
	t_environment	*begin;
	t_thread		*begin_thread;

	if (lst->next != NULL && ft_strncmp(lst->next->content, ">", 1))
		ft_printf("env: too many arguments\n");
	else
	{
		begin = terminal->lst_env;
		begin_thread = terminal->thread;
		if (terminal->thread->next)
			terminal->thread = terminal->thread->next;
		while (terminal->lst_env != NULL)
		{
			if (terminal->lst_env->exp == 1)
				ft_fill_env(terminal);
			terminal->lst_env = terminal->lst_env->next;
		}
		terminal->lst_env = begin;
		terminal->thread = begin_thread;
	}
	exit(0);
}
