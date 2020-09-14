/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsplitter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 00:52:51 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:52:38 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_cmp_set_ms(char c, int *flag, t_ms *lst, int prev)
{
	if (prev == 92 && ((*flag == 1) || (*flag & 4)))
		return (0);
	if (c == '=' && !(*flag & 2) && !(*flag & 4))
		*flag |= 8;
	if (c == 34 && !(*flag & 2) && lst != NULL)
	{
		*flag ^= 4;
		if (!(*flag & 8))
			return (1);
	}
	if (c == 39 && !(*flag & 4) && lst != NULL)
	{
		*flag ^= 2;
		if (!(*flag & 8))
			return (1);
	}
	if (c == 32)
	{
		if (!(*flag & 2) && !(*flag & 4))
			return (1);
	}
	return (0);
}

static int	parse_first_arg(char *s)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (s[i] != 0 && s[i] == 32)
		i++;
	while (s[i] != 0)
	{
		if (s[i] == 34 && flag != 2 && s[ft_iszero(i)] != 92)
			flag ^= 4;
		else if (s[i] == 39 && flag != 4 && s[ft_iszero(i)] != 92)
			flag ^= 2;
		if (flag == 0 && s[i] == 32)
			return (i);
		i++;
	}
	return (i);
}

static void	ft_check_token(t_ms **lst, t_ms *new)
{
	if (ft_strncmp(new->content, "", 1))
		ft_lstadd_back_ms(lst, new);
	else
	{
		free(new->content);
		free(new);
	}
}

void		ft_lstsplit_ms2(t_ms **lst, char *s)
{
	int		st;
	int		flag;
	int		i;
	t_ms	*new;

	flag = 1;
	i = 0;
	while (s[i] != 0)
	{
		while (s[i] != 0 && ft_cmp_set_ms(s[i], &flag, *lst,
		s[ft_iszero(i)]))
			i++;
		st = i;
		while (s[i] != 0 && !ft_cmp_set_ms(s[i], &flag, *lst,
		s[ft_iszero(i)]))
			i++;
		new = ft_lstnew_ms(ft_strndup(&s[st], i - st), s[i], flag);
		if (i > 0 && s[i] != 0 && lst != NULL && (s[i] == 32 || s[i + 1] == 32))
			new->space = 1;
		ft_check_token(lst, new);
		if (s[i] != 0 && flag == 1)
			i++;
		flag = 1;
	}
}

t_ms		*ft_lstsplit_ms(char *s)
{
	unsigned int	i;
	int				j;
	t_ms			*lst;

	i = 0;
	lst = NULL;
	j = 0;
	i = parse_first_arg(s);
	while (s[j] != 0 && s[j] == 32)
		j++;
	ft_lstadd_back_ms_ls(&lst, ft_lstnew_ms(ft_strndup(&s[j], i - j), 32, 1));
	if (!ft_strncmp(lst->content, "", 1))
	{
		free(lst->content);
		free(lst);
		lst = NULL;
		return (NULL);
	}
	s = ft_do_empty_quotes(&s[i]);
	ft_lstsplit_ms2(&lst, s);
	ft_parse_chev(lst);
	free(s);
	return (lst);
}
