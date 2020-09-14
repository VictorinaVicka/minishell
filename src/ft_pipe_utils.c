/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:32:11 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 12:11:33 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			malloc_pipe_data(t_terminal *terminal)
{
	if (!(terminal->pipes = (int **)malloc(sizeof(int *) *
	(terminal->pipe[terminal->code]
		+ 1))))
		return (0);
	if (!(terminal->cmds_pipe = (char **)malloc(sizeof(char *) *
		(terminal->pipe[terminal->code] + 1))))
		return (0);
	if (!(terminal->tab_path = (char ***)malloc(sizeof(char **) *
		(terminal->pipe[terminal->code] + 1))))
		return (0);
	if (!(terminal->split_pipe = (char ***)malloc(sizeof(char **) *
	(terminal->pipe[terminal->code] + 1))))
		return (0);
	return (1);
}

char		**ft_fill_path(char **path, char *cmd)
{
	int		i;
	char	*b;
	char	*tmp;
	char	*commande;

	i = 0;
	while (path != 0 && path[i] != 0)
	{
		b = path[i];
		commande = ft_delete_space(cmd);
		if (!(path[i] = ft_strjoin(path[i], commande)))
			return (NULL);
		free(b);
		free(commande);
		b = NULL;
		tmp = NULL;
		i++;
	}
	return (path);
}

int			init_data_pipe(t_terminal *terminal)
{
	int		i;

	i = 0;
	if (!(malloc_pipe_data(terminal)))
	{
		ft_printf("Error in malloc\n");
		safe_exit(terminal);
	}
	while (i <= terminal->pipe[terminal->cmd_pipe])
	{
		terminal->split_pipe[i] = parse_av(terminal,
		terminal->lst[terminal->code + i]);
		terminal->cmds_pipe[i] = ft_delete_space(terminal->lst
		[terminal->code + i]->content);
		if (!(terminal->tab_path[i] = ft_fill_path(parse_path(
		terminal->lst_env), terminal->cmds_pipe[i])))
			safe_exit(terminal);
		if (!(terminal->pipes[i] = malloc(sizeof(int) * 2)))
			safe_exit(terminal);
		pipe(terminal->pipes[i]);
		i++;
	}
	terminal->nb_pipe = 0;
	return (1);
}

t_thread	*get_flux(t_terminal *terminal, int nb_pipe)
{
	int i;

	i = 0;
	while (i <= nb_pipe)
	{
		if (terminal->thread->next)
			terminal->thread = terminal->thread->next;
		i++;
	}
	terminal->last = (nb_pipe == terminal->pipe[terminal->cmd_pipe]);
	return (terminal->thread);
}

int			ft_pipe(t_terminal *terminal, char **env, t_ms *lst)
{
	init_data_pipe(terminal);
	while (terminal->nb_pipe <= terminal->pipe[terminal->cmd_pipe])
	{
		if (!redir(terminal, terminal->lst[terminal->code + terminal->nb_pipe]))
			return (0);
		terminal->begin_thread = terminal->thread;
		terminal->thread = get_flux(terminal, terminal->nb_pipe);
		if ((terminal->pid = fork()) < 0)
		{
			perror("fork");
			return (4);
		}
		if (terminal->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			dup_pipe(terminal, terminal->nb_pipe);
			ft_redir_pipe(terminal);
			return (ft_exec_cmd(terminal, terminal->nb_pipe, lst, env));
		}
		else
			process_pere(terminal, terminal->nb_pipe, terminal->begin_thread);
	}
	return (0);
}
