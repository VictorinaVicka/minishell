/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:52:52 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/10 15:30:04 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		n;
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	n = size;
	if (n > 0)
		while (--n != 0)
		{
			if ((*d++ = *s++) == '\0')
				break ;
		}
	if (n == 0)
	{
		if (size > 0)
			*d = '\0';
		while (*s++)
			;
	}
	return (s - src - 1);
}
