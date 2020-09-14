/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 17:16:03 by qsymond           #+#    #+#             */
/*   Updated: 2020/05/07 17:43:57 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ret;

	i = 0;
	if ((ret = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)) != NULL)
	{
		while (s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
		ret[i] = '\0';
		return (ret);
	}
	return (NULL);
}
