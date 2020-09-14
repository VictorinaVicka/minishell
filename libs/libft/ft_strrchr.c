/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:38:47 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/01 22:59:15 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	sym;

	sym = (char)c;
	ptr = (char *)s + ft_strlen(s);
	while (ptr >= s)
	{
		if (*ptr == sym)
			return (ptr);
		ptr--;
	}
	return (NULL);
}
