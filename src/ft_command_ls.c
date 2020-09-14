/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfarenga <tfarenga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 01:02:20 by qsymond           #+#    #+#             */
/*   Updated: 2020/09/04 11:08:31 by tfarenga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_comp_end(char *end, char *cdir_name)
{
	int		i;

	i = 0;
	if (ft_strlen(end) >= ft_strlen(cdir_name) - 1)
		return (1);
	return (ft_strncmp(end, &cdir_name[ft_strlen(cdir_name) - ft_strlen(end)],
	ft_strlen(end)));
}

char		*ft_ls(char *start, char *end)
{
	struct dirent		*cdir;
	char				*ls;
	DIR					*dir;

	ls = NULL;
	if (!(dir = opendir(".")))
		return (ft_strdup(""));
	while ((cdir = readdir(dir)))
	{
		if (cdir->d_name[0] == '.' ||
		ft_strncmp(start, cdir->d_name, ft_strlen(start))
		|| ft_comp_end(end, cdir->d_name))
			continue ;
		ls = ft_shelljoin(ls, cdir->d_name);
		ls = ft_shelljoin(ls, " ");
	}
	if (ls != NULL)
		ls[ft_strlen(ls) - 1] = 0;
	closedir(dir);
	return (ls);
}
