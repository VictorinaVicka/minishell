/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:20:27 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 12:21:55 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_add_var(t_ms **alst)
{
	int		i;
	t_ms	*buffer;
	char	*s;

	buffer = *alst;
	while (buffer)
	{
		i = 0;
		s = (char*)buffer->content;
		while (s[i] != 0 && s[i] != '=')
		{
			if (!ft_isalpha(s[i]) && i == 0)
				return (0);
			if (!ft_isalnum(s[i]))
				return (0);
			i++;
		}
		if (s[i] != '=')
		{
			*alst = buffer;
			return (0);
		}
		buffer = buffer->next;
	}
	return (1);
}

static void	set_null(int *i, int *j, int *flag)
{
	*i = 0;
	*j = 0;
	*flag = 0;
}

char		*ft_parse_var_value(char *value)
{
	int		i;
	int		j;
	int		flag;
	char	*b;

	set_null(&i, &j, &flag);
	if (!(b = (char*)malloc((ft_strlen(value) + 1) * sizeof(char))))
		return (NULL);
	while (value[i] != 0)
	{
		if (value[i] != 34 && value[i] != 39)
			b[j++] = value[i];
		if (value[i] == 34 && flag == 2)
			b[j++] = value[i];
		else if (value[i] == 34 && flag == 0)
			flag = (flag == 0 ? 1 : 0);
		if (value[i] == 39 && flag == 1)
			b[j++] = value[i];
		else if (value[i] == 39 && flag == 0)
			flag = (flag == 0 ? 2 : 0);
		i++;
	}
	b[i] = 0;
	return (b);
}

void		add_var(t_terminal *terminal, t_ms *lst)
{
	int				i;
	t_environment	*environment;
	char			*s;

	while (lst)
	{
		if (!(environment = (t_environment*)malloc(sizeof(t_environment))))
			return ;
		i = 0;
		s = (char*)lst->content;
		while (s[i] != 0 && s[i] != '=')
			i++;
		environment->name = ft_strndup(s, i);
		environment->value = ft_parse_var_value(&s[i + 1]);
		environment->exp = 0;
		ft_lstadd_back_env(&terminal->lst_env, environment);
		lst = lst->next;
	}
}
