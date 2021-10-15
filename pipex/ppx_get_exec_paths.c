/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_get_exec_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:06:28 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 18:00:52 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	Returns the string in environment that starts with the word "PATH",
**	NULL if not found.
*/
static char	*ppx_get_paths_line_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

/*
**	Appends a backslash to every substring in ppx->exec_paths, -1 if the 
**	allocation failed.
*/
static int	append_backslash_to_paths(t_pipex *ppx)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ppx->exec_paths[i] != NULL)
	{
		tmp = ppx->exec_paths[i];
		ppx->exec_paths[i] = ft_strjoin(tmp, "/");
		if (ppx->exec_paths[i] == NULL)
			return (-1);
		free(tmp);
		i++;
	}
	return (0);
}

/*
**	GETS PATHS FROM ENVIRONMENT (UNIX specific)
**	Saves all executable paths in a char**, sets this to null if no variable
**	named "PATH" found in enviromnent, returns error (-1) if allocation
**	failed.
*/
int	get_exec_paths(t_pipex *ppx, char **envp)
{
	char	*env_paths_line;

	env_paths_line = ppx_get_paths_line_env(envp);
	if (env_paths_line == NULL)
	{
		ppx->exec_paths = NULL;
		return (0);
	}
	env_paths_line = ft_strchr(env_paths_line, '/');
	ppx->exec_paths = ft_split(env_paths_line, ':');
	if (ppx->exec_paths == NULL)
		return (-1);
	if (append_backslash_to_paths(ppx) != 0)
		return (-1);
	return (0);
}
