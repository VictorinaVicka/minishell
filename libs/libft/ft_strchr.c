/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:50:27 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/01 23:01:37 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char	*ptr;
	char	sym;

	ptr = (char *)s;
	sym = (char)c;
	while (*ptr && !(*ptr == sym))
		ptr++;
	if (*ptr == sym)
		return (ptr);
	else
		return (NULL);
}
