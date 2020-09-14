/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_o.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 02:02:54 by qsymond           #+#    #+#             */
/*   Updated: 2020/06/24 02:02:56 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	handle_o(char *buffer, t_arg *arg, int *count)
{
	ft_putstr_count(buffer, count, arg->w2);
}
