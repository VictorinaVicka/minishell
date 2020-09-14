/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:27:21 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/10 18:27:22 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ss;
	char	*str;
	int		l;
	int		i;

	ss = (char *)s;
	if (ss)
	{
		l = ft_strlen(ss);
		if ((str = (char *)malloc(sizeof(char) * l + 1)) == 0)
			return (0);
		i = 0;
		while (i < l)
		{
			str[i] = f(i, ss[i]);
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (0);
}
