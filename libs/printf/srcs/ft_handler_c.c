/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 02:02:44 by qsymond           #+#    #+#             */
/*   Updated: 2020/06/24 02:02:47 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	handle_c(char *buffer, t_arg *arg, int *count, int i)
{
	i = 0;
	if (arg->w1 && arg->flag != '-')
		padding(' ', arg->w1 - 1, count);
	ft_putchar_count(buffer[0], count);
	if (arg->w1 && arg->flag == '-')
		padding(' ', arg->w1 - 1, count);
}

void	handle_100(char *buffer, t_arg *arg, int *count, int i)
{
	if (arg->w1 && arg->flag != '-')
		(arg->flag == '0') ? padding('0', arg->w1 - i, count) :
		padding(' ', arg->w1 - i, count);
	ft_putstr_count(buffer, count, arg->w2);
	if (arg->w1 && arg->flag == '-')
		padding(' ', arg->w1 - i, count);
}
