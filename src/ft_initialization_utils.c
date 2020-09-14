/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialization_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:27:05 by tfarenga          #+#    #+#             */
/*   Updated: 2020/09/04 11:27:30 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_exit(t_terminal *data)
{
	if (data->cmds)
		ft_clearlist(data->cmds);
	ft_lstclear(&data->gb_collector2, free);
	exit(0);
}

int		print_exit(t_terminal *data)
{
	ft_printf("%s\n", "malloc error");
	safe_exit(data);
	exit(0);
}
