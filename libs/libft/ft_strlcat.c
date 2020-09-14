/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:14:17 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/07 22:47:55 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		n;
	size_t		i;
	char		*d;
	const char	*s;

	i = size;
	d = dst;
	s = src;
	while (i-- && *d)
		d++;
	n = d - dst;
	i = size - n;
	if (i == 0)
		return (n + ft_strlen((char *)s));
	while (*s)
	{
		if (i != 1)
		{
			*d++ = *s;
			--i;
		}
		s++;
	}
	*d = '\0';
	return (n + (s - src));
}
