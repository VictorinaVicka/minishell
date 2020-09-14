/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 00:23:44 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/10 15:24:22 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	if (dest < src)
	{
		if (n == 0 || dest == src)
			return (dest);
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
		return (dest);
	}
	while (n-- > 0)
		((char *)dest)[n] = ((char *)src)[n];
	return (dest);
}
