/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 00:47:05 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 12:18:08 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		test_directory(t_thread *thread, char *str)
{
	struct stat	buf;
	int			ret;

	ret = stat(thread->file, &buf);
	if (ret < 0)
		ft_printf("%s:%s\n:", thread->file, strerror(errno));
	if (S_ISDIR(buf.st_mode))
	{
		ft_printf("%s: is a directory\n", str);
		return (0);
	}
	return (1);
}

t_ms	*fill_databuf(t_terminal *terminal, t_ms *lst)
{
	if (!ft_strncmp(lst->content, "echo", 5) && lst->next != NULL &&
	!ft_strncmp(lst->next->content, "-n", 3))
		terminal->option_n ^= 1;
	lst = lst->next;
	if (terminal->option_n && lst)
		lst = lst->next;
	if (terminal->buf)
		free(terminal->buf);
	terminal->buf = ft_strdup(get_buffer(terminal, lst));
	terminal->test = 0;
	return (lst);
}

int		test_input(t_terminal *terminal, t_ms *lst, char *str)
{
	if (str[2] == '>' || str[2] == '<')
	{
		terminal->test = 1;
		free(terminal->buf);
		terminal->buf = ft_strdup("");
		ft_printf("syntax error near unexpected token '%c'\n", str[2]);
		return (0);
	}
	if (!lst->next)
	{
		terminal->test = 1;
		free(terminal->buf);
		terminal->buf = ft_strdup("");
		ft_printf("syntax error near unexpected token 'newline'\n");
		return (0);
	}
	return (1);
}

int		redir(t_terminal *trm, t_ms *lst)
{
	trm->begin_thread = trm->thread;
	lst = fill_databuf(trm, lst);
	while (lst)
	{
		trm->str = ft_strdup(lst->content);
		if ((trm->str[0] == '>' || trm->str[0] == '<') && lst->separator == 0)
		{
			if (!test_input(trm, lst, trm->str))
				return (0);
			if (trm->str[0] == '>' && !init_redir('w', trm, lst, trm->str))
				return (0);
			else if (trm->str[0] == '<' && !init_redir('e', trm, lst, trm->str))
				return (0);
			if (!(lst = lst->next->next))
			{
				free(trm->str);
				break ;
			}
		}
		else
			lst = lst->next;
		free(trm->str);
	}
	return (init_no_redir(trm));
}
