/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:07:48 by qsymond           #+#    #+#             */
/*   Updated: 2020/06/24 01:07:49 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_strdup_size(const char *s, size_t len)
{
	char	*new;
	size_t	i;

	if (!(new = (char *)malloc(sizeof(char) * len)))
		return (0);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	return (new);
}

void		ft_strjoin_c(char **s1, char s2)
{
	char	*copy;
	size_t	i;

	if (!s2)
		return ;
	i = ft_strlen(*s1);
	copy = ft_strdup_size(*s1, i + 2);
	copy[i] = s2;
	copy[i + 1] = '\0';
	free(*s1);
	*s1 = copy;
}
