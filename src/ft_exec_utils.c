/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:29:57 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:11:44 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_envsize(t_environment *env)
{
	int size;

	size = 0;
	while (env)
	{
		if (env->exp == 1)
			size += 1;
		env = env->next;
	}
	return (size);
}

char	**parse_env(t_environment *env)
{
	int		i;
	int		size;
	char	**envt;
	char	*tmp;

	i = 0;
	size = ft_envsize(env);
	if (!(envt = (char**)malloc((size + 1) * sizeof(char *))))
		return (NULL);
	while (i < size)
	{
		if (env->exp == 1)
		{
			tmp = ft_strjoin(env->name, "=");
			if (!(envt[i] = ft_strjoin(tmp, env->value)))
				return (NULL);
			if (tmp)
				free(tmp);
			i++;
		}
		env = env->next;
	}
	envt[i] = 0;
	return (envt);
}
