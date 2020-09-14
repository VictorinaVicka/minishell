/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 01:30:22 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:06:06 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_write_antislash(char **toprint, int *i, int sep, char *b)
{
	if (b[*i] == 92)
	{
		if (sep == 0 || (b[*i + 1] == '$' && sep != 2) ||
		(sep == 1 && b[*i + 1] == 34))
		{
			*toprint = ft_shelljoin_m(*toprint, ft_strndup(&b[++(*i)], 1));
			*i += 1;
		}
		else
		{
			*toprint = ft_shelljoin(*toprint, "\\");
			i += 1;
		}
	}
}

static void		ft_write_args2(t_terminal *terminal, char **toprint,
								char *b, int sep)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (b[i] != 0 && sep != 2)
	{
		if (b[i] != '$')
		{
			k = i;
			while (b[k] != 0 && b[k] != '$' && b[k] != 92)
				k++;
			*toprint = ft_shelljoin_m(*toprint, ft_strndup(&b[i], k - i));
			i = k;
		}
		else if (b[i] == '$' && sep != 2)
		{
			*toprint = ft_shelljoin_m(*toprint, get_var(terminal, &b[++i], &i));
			while (ft_isalnum(b[i]))
				i++;
		}
		ft_write_antislash(toprint, &i, sep, b);
	}
}

char			*ft_write_args(t_terminal *terminal, char *b, int sep)
{
	int		i;
	int		k;
	char	*toprint;

	i = 0;
	k = 0;
	toprint = ft_strdup("");
	if (sep == 2)
	{
		toprint = ft_shelljoin(toprint, b);
		return (add_garbage_ret(terminal, (void**)&toprint));
	}
	else
		ft_write_args2(terminal, &toprint, b, sep);
	return (add_garbage_ret(terminal, (void**)&toprint));
}

char			*get_var(t_terminal *terminal, char *b, int *inc)
{
	int		i;
	char	*name;

	i = 0;
	if (!ft_strncmp(b, "?", 1))
	{
		*inc += 1;
		return (ft_strdup(get_var_env(terminal->lst_env, "?")));
	}
	if (!ft_isalnum(b[i]))
	{
		return (ft_strdup("$"));
	}
	while (b[i] != 0 && ft_isalnum(b[i]))
		i++;
	name = ft_strndup(b, i);
	*inc += i;
	if (name == NULL || ft_strlen(name) == 0)
	{
		free(name);
		return (ft_strdup(""));
	}
	free(name);
	return (ft_strdup(get_var_env(terminal->lst_env, name)));
}

char			*get_var_env(t_environment *env, char *name)
{
	while (env != NULL)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(env->name) + 1))
			return (env->value);
		env = env->next;
	}
	return ("");
}
