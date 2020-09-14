/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:41:47 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:11:07 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**parse_path_null(void)
{
	char	**path;

	if (!(path = (char**)malloc(2 * sizeof(char*))))
		return (NULL);
	path[0] = ft_strdup("");
	path[1] = 0;
	return (path);
}

char		**parse_path(t_environment *env)
{
	char	**path;
	int		i;

	i = 0;
	while (env)
	{
		if (!ft_strncmp(env->name, "PATH", 5))
		{
			path = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
		path = parse_path_null();
	else
	{
		while (path[i] != 0)
		{
			path[i] = ft_shelljoin(path[i], "/");
			i++;
		}
	}
	return (path);
}

int			ft_exec_cmd(t_terminal *terminal, int nb_pipe,
						t_ms *lst, char **env)
{
	int i;

	test_builtin(terminal);
	if (ft_strncmp(terminal->cmds_pipe[nb_pipe], "pwd", 4) == 0)
		ft_pwd(terminal);
	else if (ft_strncmp(terminal->cmds_pipe[nb_pipe], "env", 4) == 0)
		ft_env(terminal, lst);
	else if (ft_strncmp(terminal->cmds_pipe[nb_pipe], "export", 7) == 0)
		ft_export_no_arg(terminal);
	else
	{
		i = 0;
		if (execve(lst->content, terminal->split_pipe[nb_pipe], env) != -1)
			return (1);
		while (execve(terminal->tab_path[nb_pipe][i],
		terminal->split_pipe[nb_pipe],
			env) == -1 && terminal->tab_path[nb_pipe][i] != NULL)
			i++;
		test_path(terminal, i);
		test_path_null(terminal, i);
	}
	return (4);
}
