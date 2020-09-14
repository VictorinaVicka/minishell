/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 13:17:32 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 12:07:39 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parse_commands(t_terminal *trm)
{
	int		j;
	char	*s;
	t_ms	*b;

	j = 0;
	parse_separators(trm);
	trm->n_cmds = ft_strlen(trm->sep) + 1;
	j = 0;
	trm->cmds = ft_split_ms(trm->entry, "|;&\n", trm->n_cmds);
	trm->lst = malloc((trm->n_cmds + 1) * sizeof(t_list*));
	while (trm->cmds[j] != 0)
	{
		trm->lst[j] = ft_lstsplit_ms(trm->cmds[j]);
		if (trm->lst[j] != 0)
		{
			s = ft_strjoin("|arg|-| ", trm->lst[j]->content);
			b = ft_lstsplit_ms(s);
			free(trm->lst[j]->content);
			free(s);
			trm->lst[j]->content = ft_strdup(get_buffer(trm, b->next));
			ft_lstclear_ms(&b, free);
		}
		j++;
	}
	trm->lst[j] = 0;
}
