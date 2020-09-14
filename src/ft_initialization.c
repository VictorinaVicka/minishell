/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 01:25:59 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:35:10 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_copyuntil(char **dst, char *src, char c)
{
	int		j;
	int		i;
	char	*buf;

	j = -1;
	while (src[++j])
		if (src[j] == c)
			break ;
	if (!(buf = ft_strnew(j)))
		return (0);
	i = 0;
	while (i < j && src[i])
	{
		buf[i] = src[i];
		i++;
	}
	buf[i] = '\0';
	*dst = buf;
	return (j);
}

void			ft_lstadd_back_env(t_environment **alst, t_environment *new)
{
	t_environment *tmp;

	if (*alst && new)
	{
		tmp = *alst;
		if (!(*alst))
		{
			*alst = new;
			return ;
		}
		while (tmp != NULL && tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
	else if (alst)
		*alst = new;
	return ;
}

t_environment	*init_href(char *name, char *value, int exp)
{
	t_environment *new_env;

	if (!(new_env = malloc(sizeof(t_environment))))
		return (0);
	new_env->name = name;
	new_env->value = value;
	new_env->exp = exp;
	new_env->next = NULL;
	return (new_env);
}

t_environment	*init_environment(char **envp)
{
	int				j;
	char			*str;
	char			*name;
	char			*value;
	t_environment	*list;

	name = NULL;
	value = NULL;
	list = NULL;
	while (*envp != NULL)
	{
		str = *envp;
		j = ft_copyuntil(&name, str, '=');
		ft_copyuntil(&value, &str[j + 1], '\0');
		ft_lstadd_back_env(&list, init_href(name, value, 1));
		envp++;
	}
	ft_lstadd_back_env(&list, init_href("?", ft_strdup("0"), 0));
	return (list);
}

void			initialization(t_terminal *terminal, char **envp,
								int argc, char **av)
{
	terminal->n_cmds = 0;
	argc = 1;
	av[0] = "";
	terminal->gb_collector2 = NULL;
	terminal->i = 0;
	terminal->cmds = NULL;
	terminal->sep = NULL;
	terminal->lst = NULL;
	terminal->buf = NULL;
	terminal->envp = envp;
	terminal->lst_env = init_environment(envp);
	if (!(terminal->thread = (t_thread *)malloc(sizeof(t_thread))))
		print_exit(terminal);
	terminal->code = 0;
	terminal->thread->fd = 1;
	terminal->first = 1;
	terminal->thread->redirect = 'z';
	terminal->split_pipe = NULL;
	terminal->tab_path = NULL;
	terminal->cmd_pipe = 0;
	terminal->cmds_pipe = NULL;
	if (!(terminal->pipe = (int *)malloc(sizeof(int) * 100)))
		print_exit(terminal);
	terminal->option_n = 0;
}
