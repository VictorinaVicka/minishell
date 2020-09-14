/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:07:40 by qsymond           #+#    #+#             */
/*   Updated: 2020/06/24 01:07:42 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_strdup(const char *s1)
{
	int		index;
	char	*returned_string;

	index = 0;
	if (!(returned_string = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	while (s1[index])
	{
		returned_string[index] = s1[index];
		index++;
	}
	returned_string[index] = '\0';
	return (returned_string);
}
