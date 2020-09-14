/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:18:56 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:14:45 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_a_cmd(t_terminal *terminal, t_ms *lst)
{
	char	**envt;
	int		i;
	int		ret;
	int		size;

	size = ft_envsize(terminal->lst_env);
	envt = parse_env(terminal->lst_env);
	ret = ft_pipe(terminal, envt, lst);
	if (ret != 0)
		ft_printf("error : %d\n", ret);
	i = 0;
	while (i < size)
	{
		free(envt[i]);
		envt[i] = NULL;
		i++;
	}
	free(envt[i]);
	free(envt);
	return (1);
}

void	cmd_without_pipe(t_terminal *terminal, t_ms *lst, int i)
{
	if (terminal->pipe[terminal->code] > 0)
	{
		terminal->pipe[terminal->cmd_pipe] -= 1;
		terminal->code += 1;
		exec_a_cmd(terminal, lst);
		free_pipe_cmd(terminal);
	}
	else
	{
		if (i == 1 && ft_cd(terminal, lst) == 1)
			ft_error(terminal, 1);
		else if (i == 2)
			ft_exit(terminal, lst);
		else if (i == 3)
			ft_unset(&terminal, lst);
		else if (i == 4)
			ft_export(terminal, lst);
	}
	return ;
}

void	test_pipe_export(t_terminal *terminal, t_ms *lst)
{
	if (!terminal->pipe[terminal->code])
		cmd_without_pipe(terminal, lst, 4);
	else
		terminal->no_arg = 0;
}

void	exec_cmd(t_terminal *trm, t_ms *lst)
{
	trm->no_arg = 1;
	if (lst == NULL)
		return ;
	if (is_add_var(&lst))
	{
		add_var(trm, lst);
		return ;
	}
	else if (ft_strncmp(lst->content, "cd", 3) == 0 &&
	!trm->pipe[trm->code])
		cmd_without_pipe(trm, lst, 1);
	else if (ft_strncmp(lst->content, "exit", 5) == 0 &&
		!trm->pipe[trm->code])
		cmd_without_pipe(trm, lst, 2);
	else if (ft_strncmp(lst->content, "unset", 6) == 0 &&
		!trm->pipe[trm->code])
		cmd_without_pipe(trm, lst, 3);
	else if (ft_strncmp(lst->content, "export", 7) == 0 && (lst->next != NULL
	&& ft_strncmp(ft_write_args(trm, get_buffer(trm, lst->next), 0), "", 1)))
		test_pipe_export(trm, lst);
	else
	{
		exec_a_cmd(trm, lst);
		free_pipe_cmd(trm);
	}
}
