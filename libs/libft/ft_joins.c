/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 01:17:36 by qsymond           #+#    #+#             */
/*   Updated: 2020/08/31 01:18:56 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_shelljoin(char const *s1, char const *s2)
{
	size_t			megasize;
	char			*b;
	size_t			len_1;
	size_t			len_2;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	megasize = len_1 + len_2;
	if (!(b = (char *)malloc((megasize + 1) * sizeof(char))))
		return (NULL);
	b[0] = 0;
	ft_strcat(b, s1, 0);
	free((char*)s1);
	ft_strcat(b, s2, len_1);
	return (b);
}

char		*ft_shelljoin_m(char const *s1, char const *s2)
{
	size_t			megasize;
	char			*b;
	size_t			len_1;
	size_t			len_2;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	megasize = len_1 + len_2;
	if (!(b = (char *)malloc((megasize + 1) * sizeof(char))))
		return (NULL);
	b[0] = 0;
	ft_strcat(b, s1, 0);
	free((char*)s1);
	ft_strcat(b, s2, len_1);
	free((char*)s2);
	return (b);
}
