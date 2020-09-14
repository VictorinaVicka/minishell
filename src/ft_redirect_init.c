/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 12:17:07 by tfarenga          #+#    #+#             */
/*   Updated: 2020/09/04 12:17:31 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_redir(char c, t_terminal *terminal, t_ms *lst, char *str)
{
	t_thread *new_thread;

	terminal->test = 1;
	if (!(new_thread = (t_thread *)malloc(sizeof(t_thread))))
		return (0);
	new_thread->redirect = c;
	if (str[1] == '>' && str[0] == '>')
		new_thread->redirect = 'a';
	new_thread->file = ft_strdup(lst->next->content);
	if (c == 'e')
		new_thread->fd = open(new_thread->file, O_RDWR);
	else
		new_thread->fd = open(new_thread->file, O_RDWR | O_CREAT, 0644);
	close(new_thread->fd);
	if (!test_directory(new_thread, new_thread->file))
		return (0);
	new_thread->next = NULL;
	ft_lstadd_back_flux(&terminal->thread, new_thread);
	return (1);
}

int		init_no_redir(t_terminal *terminal)
{
	t_thread *new_thread;

	if (terminal->test == 0)
	{
		if (!(new_thread = (t_thread *)malloc(sizeof(t_thread))))
			safe_exit(terminal);
		new_thread->redirect = 'z';
		new_thread->file = NULL;
		new_thread->fd = 1;
		new_thread->next = NULL;
		ft_lstadd_back_flux(&terminal->thread, new_thread);
	}
	terminal->thread = terminal->begin_thread;
	return (1);
}
