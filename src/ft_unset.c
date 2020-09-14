/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:22:10 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 12:20:45 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_unset_var(t_environment *lst_env, int option)
{
	free(lst_env->name);
	free(lst_env->value);
	lst_env->name = NULL;
	lst_env->value = NULL;
	lst_env->exp = 0;
	if (option == 1)
		free(lst_env);
	return (0);
}

void	ft_unset_boucle(t_terminal **terminal, char *args)
{
	while ((*terminal)->lst_env && (*terminal)->lst_env->next)
	{
		if (ft_strncmp(args, (*terminal)->lst_env->next->name,
			ft_strlen(args)) == 0)
		{
			ft_unset_var((*terminal)->lst_env->next, 2);
			free((*terminal)->lst_env->next);
			(*terminal)->lst_env->next = (*terminal)->lst_env->next->next;
		}
		(*terminal)->lst_env = (*terminal)->lst_env->next;
	}
}

void	ft_unset(t_terminal **trm, t_ms *lst)
{
	t_environment	*begin;
	char			*args;

	args = NULL;
	begin = (*trm)->lst_env;
	if (!lst->next)
		return ;
	while ((lst = lst->next))
	{
		if ((*trm)->lst_env)
		{
			args = ft_strdup(ft_write_args(*trm, lst->content, 1));
			if (ft_strncmp(args, (*trm)->lst_env->name, ft_strlen(args)) == 0)
			{
				begin = (*trm)->lst_env->next;
				ft_unset_var((*trm)->lst_env, 1);
			}
		}
		ft_unset_boucle(trm, args);
		free(args);
		(*trm)->lst_env = begin;
	}
	(*trm)->buf = ft_strdup("");
	(*trm)->option_n = 1;
	write_redir((*trm));
}
