/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:45:16 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 12:12:25 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		dup_pipe(t_terminal *terminal, int nb_pipe)
{
	int i;

	terminal->unique = (terminal->last && terminal->first);
	if (!terminal->unique)
	{
		if (!terminal->last)
			dup2(terminal->pipes[nb_pipe][1], STDOUT_FILENO);
		if (!terminal->first)
			dup2(terminal->pipes[nb_pipe - 1][0], STDIN_FILENO);
	}
	i = 0;
	while (i < terminal->pipe[terminal->code])
	{
		if (i != nb_pipe && i != nb_pipe - 1)
			ft_close(terminal, i);
		i++;
	}
	if (!terminal->first)
		ft_close(terminal, nb_pipe - 1);
	ft_close(terminal, nb_pipe);
	return (0);
}

void	ft_redir_pipe(t_terminal *terminal)
{
	if ((terminal->thread->redirect == 'a' ||
								terminal->thread->redirect == 'w'))
	{
		if (terminal->thread->redirect == 'a')
			terminal->redir_out = open(terminal->thread->file, O_RDWR
			| O_CREAT | O_APPEND);
		if (terminal->thread->redirect == 'w')
			terminal->redir_out = open(terminal->thread->file, O_RDWR
			| O_CREAT | O_TRUNC);
		if (terminal->redir_out < 0)
			ft_error_message(terminal);
		dup2(terminal->redir_out, STDOUT_FILENO);
		close(terminal->redir_out);
	}
	else if (terminal->thread->redirect == 'e')
	{
		terminal->redir_in = open(terminal->thread->file, O_RDWR);
		if (terminal->redir_in < 0)
			ft_error_message(terminal);
		dup2(terminal->redir_in, STDIN_FILENO);
		close(terminal->redir_in);
	}
}

void	free_thread(t_terminal *terminal)
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

void	free_pipe_cmd(t_terminal *terminal)
{
	int i;

	i = 0;
	while (i < terminal->pipe[terminal->cmd_pipe] + 1)
	{
		free_double_tab(terminal->split_pipe, i);
		ft_strdel(&terminal->cmds_pipe[i]);
		if (terminal->pipes)
		{
			if (terminal->pipes[i])
			{
				free(terminal->pipes[i]);
				terminal->pipes[i] = NULL;
			}
		}
		free_double_tab(terminal->tab_path, i);
		i++;
	}
	if (terminal->cmds_pipe)
		free(terminal->cmds_pipe);
	if (terminal->tab_path)
		free(terminal->tab_path);
	if (terminal->split_pipe)
		free(terminal->split_pipe);
	free_thread(terminal);
}

int		process_pere(t_terminal *terminal, int nb_pipe, t_thread *begin)
{
	int ret;
	int status;

	terminal->child = 1;
	while (terminal->child)
	{
		if (!terminal->first)
			close(terminal->pipes[nb_pipe - 1][1]);
		ret = wait(&status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				ft_error(terminal, 130);
			else if (WTERMSIG(status) == 3)
				ft_error(terminal, 131);
		}
		else
			ft_error(terminal, WEXITSTATUS(status));
		if (ret == terminal->pid)
			terminal->child = 0;
	}
	terminal->first = 0;
	terminal->nb_pipe += 1;
	terminal->thread = begin;
	return (0);
}
