/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handler_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:55:47 by qsymond           #+#    #+#             */
/*   Updated: 2020/06/24 01:56:03 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	handle_s(char *buffer, t_arg *arg, int *count, int i)
{
	if (arg->flag != '-')
		padding((arg->flag == '0' ? '0' : ' '), arg->w1 -
		((arg->w2 < i && (arg->w2 > 0 || arg->precision == '.')
		&& arg->w2 >= 0) ? arg->w2 : i), count);
	if (!(arg->precision == '.' && arg->w2 == 0))
		ft_putstr_count(buffer, count, (i < arg->w2 && arg->precision
		== '.') ? i : arg->w2);
	if (arg->flag == '-')
		padding(' ', arg->w1 - ((arg->w2 < i && arg->w2 >= 0 &&
		arg->precision == '.') ? arg->w2 : i), count);
}
