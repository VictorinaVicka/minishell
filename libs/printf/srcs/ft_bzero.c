/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:06:41 by qsymond           #+#    #+#             */
/*   Updated: 2020/06/24 01:06:44 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_bzero(void *s, unsigned int n)
{
	unsigned char	*d;
	unsigned int	index;

	index = 0;
	d = (unsigned char *)s;
	while (index < n)
	{
		d[index] = '\0';
		index++;
	}
}
