/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_separators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 23:41:11 by qsymond           #+#    #+#             */
/*   Updated: 2020/08/31 01:48:20 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_flag(t_terminal *terminal, int flag, int i)
{
	if (terminal->entry[i] == 34 && flag != 2)
		flag = (flag == 0 ? 1 : 0);
	if (terminal->entry[i] == 39 && flag != 1)
		flag = (flag == 0 ? 2 : 0);
	return (flag);
}

static void	set_separator(t_terminal *terminal, int i, int *j, int *k)
{
	if (i > 0 && terminal->entry[i - 1] != 92)
	{
		terminal->sep = ft_shelljoin_m(terminal->sep, \
		ft_strndup(&terminal->entry[i], 1));
		*j += 1;
		if (terminal->entry[i] == '|' && (*j > 0 && (!terminal->sep[*j] ||
		terminal->sep[*j - 1] == '|')))
		{
			if (terminal->entry[i + 1] && terminal->entry[i + 1] == '|')
			{
				ft_printf("Parsing error with '|'\n");
				free(terminal->entry);
				terminal->entry = ft_strdup("\0");
			}
			terminal->pipe[*k] += 1;
		}
		else
		{
			*k += 1;
			terminal->pipe[*k] = 0;
		}
	}
}

void		parse_separators(t_terminal *terminal)
{
	int i;
	int j;
	int k;
	int flag;

	i = 0;
	j = 0;
	k = 0;
	flag = 0;
	terminal->sep = ft_strdup("");
	while (terminal->entry[i] != 0)
	{
		if (terminal->entry[ft_iszero(i)] != 92)
			flag = get_flag(terminal, flag, i);
		if (terminal->entry[ft_iszero(i)] == 92 && flag == 2)
			flag = get_flag(terminal, flag, i);
		if (flag == 0 && ft_isseparator(terminal->entry[i]))
			set_separator(terminal, i, &j, &k);
		i++;
	}
	terminal->sep[j] = 0;
}
