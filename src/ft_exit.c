/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 00:15:25 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/03 01:24:38 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		str_is_digit(t_ms *lst)
{
	int		i;
	char	*str;

	i = 0;
	if (lst->next)
	{
		str = ft_strdup(lst->next->content);
		while (str[i])
		{
			if (!ft_isdigit(str[i]))
			{
				free(str);
				return (0);
			}
			i++;
		}
		free(str);
	}
	else
		return (0);
	return (1);
}

void	ft_exit(t_terminal *terminal, t_ms *lst)
{
	int		flag;
	char	*str;

	flag = str_is_digit(lst);
	str = NULL;
	if (lst->next && lst->next->next && lst->next->next->content)
		str = ft_strdup(lst->next->next->content);
	if (lst->next == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	else if (flag == 1 && str != NULL)
	{
		ft_printf("exit\nexit: too many arguments\n");
		ft_error(terminal, 1);
		free(str);
	}
	else
	{
		ft_printf("exit\n");
		if (flag == 0)
			ft_printf("exit : numeric argument required\n");
		exit(ft_atoi(lst->next->content));
	}
}
