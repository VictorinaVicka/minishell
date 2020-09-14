/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 14:41:44 by qsymond           #+#    #+#             */
/*   Updated: 2020/08/29 17:29:04 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	result;
	int	sign;

	while (*str == '\n' || *str == '\r' || \
	*str == '\v' || *str == '\f' || *str == '\t' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0;
	while ((*str >= '0' && *str <= '9') && *str)
	{
		if ((unsigned long)__LONG_MAX__ < ((unsigned long)result * 10 + (*str -
						'0')) && sign == 1)
			return (-1);
		else if ((unsigned long)__LONG_MAX__ < ((unsigned long)result * 10 +
						(*str - '0')) && sign == -1)
			return (0);
		result = 10 * result + *str - '0';
		str++;
	}
	return (result * sign);
}
