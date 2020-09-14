/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:12:43 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:53:52 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_error_sep(t_terminal *terminal)
{
	ft_printf("Parse error near 'end of file'\n");
	ft_error(terminal, 258);
	return (0);
}

int		ft_check_pipes(t_terminal *terminal)
{
	int i;

	i = 0;
	while (terminal->sep[i] != 0)
	{
		if (terminal->sep[i] == '|' && terminal->cmds[i + 1] == 0)
			return (ft_error_sep(terminal));
		else if (terminal->sep[i] == '|' && ft_is_empty(terminal->cmds[i + 1]))
			return (ft_error_sep(terminal));
		else if (terminal->sep[i] == ';' && terminal->sep[i + 1] == ';')
		{
			if (terminal->cmds[i + 1] == 0)
				return (ft_error_sep(terminal));
			else if (ft_is_empty(terminal->cmds[i + 1]))
				return (ft_error_sep(terminal));
		}
		i++;
	}
	return (1);
}
