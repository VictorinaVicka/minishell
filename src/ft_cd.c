/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:12:15 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:07:02 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_set_pwd(t_environment *env)
{
	while (env)
	{
		if (!ft_strncmp("PWD", env->name, 4))
		{
			free(env->value);
			env->value = getcwd(0, 0);
			break ;
		}
		env = env->next;
	}
}

static	void	ft_cd_home(t_environment *env)
{
	t_environment	*env2;

	env2 = env;
	while (env)
	{
		if (!ft_strncmp(env->name, "HOME", 5))
		{
			chdir(env->value);
			ft_set_pwd(env2);
			return ;
		}
		env = env->next;
	}
	ft_printf("home not set\n");
	return ;
}

static int		ft_cd_error(char *path)
{
	ft_printf("%s: cd: %s: no such file or directory\n", PROMPT, path);
	return (1);
}

int				ft_cd(t_terminal *terminal, t_ms *lst)
{
	int				i;
	char			*path;
	t_environment	*env;

	i = 0;
	env = terminal->lst_env;
	path = NULL;
	if (lst->next != NULL && lst->next->content != NULL)
		path = get_buffer(terminal, lst->next);
	if (lst->next == NULL || !ft_strncmp(path, "", 1))
	{
		ft_cd_home(env);
		return (0);
	}
	else
	{
		i = chdir(path);
		if (i != 0)
			return (ft_cd_error(path));
		ft_set_pwd(env);
	}
	terminal->buf = ft_strdup("");
	terminal->option_n = 1;
	write_redir(terminal);
	return (0);
}
