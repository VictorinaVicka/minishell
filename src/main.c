/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 18:03:51 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 12:55:15 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd(t_terminal *terminal)
{
	terminal->pipes = NULL;
	terminal->tab_path = NULL;
	terminal->cmds_pipe = NULL;
	terminal->args_pipe = NULL;
	terminal->split_pipe = NULL;
	terminal->first = 1;
	terminal->thread->redirect = 'z';
}

void	reinit(t_terminal *terminal)
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

void	ft_free_all(t_terminal *terminal)
{
	ft_free_lst(terminal->lst);
	free_cmds(terminal->cmds);
	ft_lstclear(&terminal->gb_collector2, free);
}

int		main(int argc, char **argv, char **envp)
{
	t_terminal	trm;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	initialization(&trm, envp, argc, argv);
	while (1)
	{
		ft_printf("%s$: ", PROMPT);
		parse_input(&trm);
		if (trm.entry == NULL)
			return (ft_printf("exiting...\n"));
		parse_commands(&trm);
		while (trm.entry && trm.lst[trm.code] != NULL && trm.lst != NULL)
		{
			if (!ft_check_pipes(&trm))
				break ;
			exec_cmd(&trm, trm.lst[trm.code]);
			init_cmd(&trm);
			trm.code += trm.pipe[trm.cmd_pipe] + 1;
			trm.cmd_pipe++;
		}
		ft_free_all(&trm);
		reinit(&trm);
	}
	clear_memory(&trm);
	return (0);
}
