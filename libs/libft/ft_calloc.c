/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:50:51 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 12:50:21 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, unsigned int n)
{
	unsigned char	*d;
	unsigned int	index;

	index = 0;
	d = (unsigned char *)s;
	while (index < n)
	{
		d[index] = '\0';
		index++;
	}
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*new;

	if ((new = (void *)malloc(size * num)) != NULL)
	{
		ft_bzero(new, num * size);
		return (new);
	}
	return (NULL);
}
