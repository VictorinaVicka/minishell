/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_without_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:00:52 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/03 00:09:11 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_abs(int x)
{
	return (x < 0 ? -x : x);
}

static void		ft_sort(char **tab)
{
	int		i;
	int		j;
	int		n;
	char	*b;

	i = 0;
	j = 0;
	while (tab[i] != 0)
	{
		j = i + 1;
		while (tab[j] != 0)
		{
			n = ft_abs(ft_strchr(tab[i], '=') - ft_strchr(tab[j], '='));
			if (ft_strncmp(tab[i], tab[j], n) > 0)
			{
				b = tab[i];
				tab[i] = tab[j];
				tab[j] = b;
			}
			else
				j++;
		}
		i++;
	}
	tab[i - 1][ft_strlen(tab[i - 1]) - 1] = 0;
}

static void		ft_fill_tab(char **tab, t_environment *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->exp)
		{
			tab[i] = ft_strjoin("declare -x ", env->name);
			tab[i] = ft_shelljoin(tab[i], "=\"");
			tab[i] = ft_shelljoin_m(tab[i], ft_strjoin(env->value, "\"\n"));
			i++;
		}
		env = env->next;
	}
	tab[i] = 0;
}

void			ft_export_no_arg(t_terminal *terminal)
{
	char	**tab;
	int		i;
	int		size;

	size = ft_envsize(terminal->lst_env);
	i = 0;
	if (!(tab = (char**)malloc(sizeof(char*) * (size + 1))))
		return ;
	ft_fill_tab(tab, terminal->lst_env);
	ft_sort(tab);
	while (tab[i] != 0)
		terminal->buf = ft_shelljoin(terminal->buf, tab[i++]);
	i = 0;
	write_redir(terminal);
	while (size)
		free(tab[size--]);
	free(tab);
	exit(0);
}
