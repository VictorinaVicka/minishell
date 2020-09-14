/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:11:55 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/10 17:11:59 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long nn;
	char c;

	nn = n;
	if (nn < 0)
	{
		write(fd, "-", 1);
		nn = -nn;
	}
	if (nn >= 10)
	{
		ft_putnbr_fd(nn / 10, fd);
		c = nn % 10 + '0';
		write(fd, &c, 1);
	}
	else
	{
		c = nn + '0';
		write(fd, &c, 1);
	}
}
