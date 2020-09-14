/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:19:49 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:16:12 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_new_export(t_terminal *terminal, char *name_env,
						char *value_env, int k)
{
	t_environment *new_env;

	if (terminal->test == 0 && terminal->nb_export < LIMIT_EXPORT)
	{
		if (!(new_env = malloc(sizeof(t_environment))))
			return (0);
		new_env->name = name_env;
		if (k)
			new_env->value = value_env;
		else
			new_env->value = ft_strdup("''");
		new_env->exp = 1;
		new_env->next = NULL;
		ft_lstadd_back_env(&terminal->lst_env, new_env);
	}
	else if (terminal->test == 0 && terminal->nb_export >= LIMIT_EXPORT)
		ft_printf("limit reached\n");
	return (1);
}

void		test_env(t_terminal *data, t_ms *lst, int j, char *str)
{
	t_environment	*begin;
	char			*value_env;
	int				k;

	begin = data->lst_env;
	data->test = 0;
	data->nb_export = 1;
	while (data->lst_env)
	{
		if (ft_strncmp(data->lst_env->name, lst->content,
		ft_strlen(data->lst_env->name)) == 0)
		{
			if (str[j] == '=')
			{
				k = ft_copyuntil(&value_env, &str[j + 1], '\0');
				free(data->lst_env->value);
				data->lst_env->value = (k > 0 ? value_env : ft_strdup("''"));
			}
			data->lst_env->exp = 1;
			data->test = 1;
		}
		data->nb_export += 1;
		data->lst_env = data->lst_env->next;
	}
	data->lst_env = begin;
}

static t_ms	*ft_export_get_args2(t_ms *lst, t_ms **lst_b)
{
	while (lst && lst->space == 0)
	{
		ft_lstadd_back_ms(lst_b, ft_lstnew_ms(ft_strdup(lst->content),
		lst->separator, 1));
		if (lst->next && lst->next->space == 1)
		{
			ft_lstadd_back_ms(lst_b, ft_lstnew_ms(ft_strdup(lst->next->content),
			lst->next->separator, 1));
		}
		lst = lst->next;
	}
	return (lst);
}

t_ms		*ft_export_get_args(t_terminal *terminal, t_ms *lst, char **b)
{
	t_ms	*lst_b;

	lst_b = 0;
	*b = ft_strdup("");
	if (lst->space == 0)
	{
		lst = ft_export_get_args2(lst, &lst_b);
		free(*b);
		*b = get_buffer(terminal, lst_b);
		if (lst)
		{
			ft_lstclear_ms(&lst_b, free);
			return (lst->next);
		}
	}
	else
	{
		ft_lstadd_back_ms_ls(&lst_b, ft_lstnew_ms(ft_strdup(lst->content),
		lst->separator, 0));
		free(*b);
		*b = get_buffer(terminal, lst_b);
		lst = lst->next;
	}
	ft_lstclear_ms(&lst_b, free);
	return (lst);
}

void		ft_export(t_terminal *terminal, t_ms *lst)
{
	char	*name_env;
	char	*value_env;
	int		jk[2];
	char	*args;
	t_ms	*lst_next;

	lst = lst->next;
	while (lst)
	{
		jk[0] = 0;
		jk[1] = 0;
		lst_next = ft_export_get_args(terminal, lst, &args);
		if (!(args = ft_strdup(args)))
			break ;
		jk[0] = ft_copyuntil(&name_env, args, '=');
		jk[1] = ft_copyuntil(&value_env, &args[jk[0] + 1], '\0');
		test_env(terminal, lst, jk[0], args);
		ft_new_export(terminal, name_env, value_env, jk[1]);
		free(args);
		lst = lst_next;
	}
	terminal->buf = ft_strdup("");
	terminal->option_n = 1;
	write_redir(terminal);
}
