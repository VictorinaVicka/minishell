/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 21:23:16 by qsymond           #+#    #+#             */
/*   Updated: 2020/08/29 21:23:35 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_addchar(char const *s1, char c)
{
	char	*new_str;
	size_t	i;
	size_t	s1_len;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	new_str = ft_strnew(s1_len + 2);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		*(new_str + i) = *(s1 + i);
	*(new_str + i) = c;
	return (new_str);
}
