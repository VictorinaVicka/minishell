/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsplitter2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 00:54:30 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:53:21 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_if_last(char *s, int i)
{
	while (s[i] != 0)
	{
		if (s[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

static void	ft_do_empty_quotes2(char **b, int *i, int *flag,
								t_var_splitter_m *var)
{
	if (var->cmp == 1 && var->s[*i] == 34 && (*flag & 4) && !(*flag & 2) &&
	!check_if_last(var->s, *i + 2) && var->s[*i + 1] == 34)
	{
		if (var->s[*i + 2] != 0 && var->s[*i + 2] == 32)
		{
			*b = ft_shelljoin(*b, "\" \"");
			*flag = 1;
			*i += 3;
		}
	}
	else if (var->cmp == 1 && var->s[*i] == 39 && (*flag & 2) && !(*flag & 4) &&
	!check_if_last(var->s, *i + 2) && var->s[*i + 1] == 39)
	{
		if (var->s[*i + 2] != 0 && var->s[*i + 2] == 32)
		{
			*b = ft_shelljoin(*b, "\' \'");
			*flag = 1;
			*i += 3;
		}
	}
	else
		*b = ft_shelljoin_m(*b, ft_strndup(&var->s[(*i)++], 1));
}

char		*ft_do_empty_quotes(char *s)
{
	int					i;
	int					flag;
	t_ms				nada;
	char				*b;
	t_var_splitter_m	var;

	i = 0;
	flag = 1;
	b = ft_strdup("");
	var.s = s;
	while (s[i] != 0)
	{
		var.cmp = ft_cmp_set_ms(s[i], &flag, &nada, ft_iszero(i));
		ft_do_empty_quotes2(&b, &i, &flag, &var);
	}
	return (b);
}
