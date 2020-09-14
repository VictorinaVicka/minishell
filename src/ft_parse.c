/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:54:13 by tfarenga          #+#    #+#             */
/*   Updated: 2020/09/04 11:54:16 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		handler(int i)
{
	ft_printf("\n%s$:", PROMPT);
	i = 0;
}

void		parse_input(t_terminal *data)
{
	int		ret;
	char	*b_line;
	char	buffer[1024];

	data->entry = NULL;
	while ((ret = read(STDIN_FILENO, buffer, 1)) >= 0)
	{
		buffer[ret] = 0;
		if (ret == 0 && data->entry == NULL)
			return ;
		if (buffer[0] == EOF)
			continue ;
		signal(SIGINT, handler);
		b_line = data->entry;
		data->entry = ft_addchar(b_line, buffer[0]);
		free(b_line);
		b_line = NULL;
		if (ft_checkchar(data->entry, '\n'))
			break ;
	}
	if (ret < 0)
		perror("Reading: \n");
}
