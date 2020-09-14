/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:42:30 by qsymond           #+#    #+#             */
/*   Updated: 2020/08/29 17:13:38 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	long	myabs(int n)
{
	long nn;

	nn = (long)n;
	return (nn < 0 ? -nn : nn);
}

static	int		power10(int n)
{
	int p;

	p = 1;
	while (n-- > 1)
		p *= 10;
	return (p);
}

static	int		nbrlen(long n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static	char	*mymalloc(int n, int size)
{
	char *itoa;

	if (n <= 0)
		itoa = (char *)malloc(sizeof(char) * (size + 2));
	else
		itoa = (char *)malloc(sizeof(char) * (size + 1));
	if (!itoa)
		return (0);
	return (itoa);
}

char			*ft_itoa(int n)
{
	long	absn;
	int		size;
	int		mod;
	char	*itoa;
	int		i;

	absn = myabs(n);
	size = nbrlen(absn);
	mod = power10(size);
	itoa = mymalloc(n, size);
	if (!itoa)
		return (0);
	i = 0;
	if (n < 0)
		itoa[i++] = '-';
	else if (n == 0)
		itoa[i++] = '0';
	while (size--)
	{
		itoa[i++] = (absn / mod) + '0';
		absn %= mod;
		mod /= 10;
	}
	itoa[i] = '\0';
	return (itoa);
}
