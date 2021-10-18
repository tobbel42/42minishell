/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_exec_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:43:05 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/18 13:26:02 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"


/*
**	Appends a backslash to every substring in ms->exec_paths, -1 if the 
**	allocation failed.
*/
static int	ms_append_backslash_to_paths(t_ms_data	*ms)
{
	char	*tmp;
	int		i;

	i = 0;
	while (ms->exec_paths[i] != NULL)
	{
		tmp = ms->exec_paths[i];
		ms->exec_paths[i] = ft_strjoin(tmp, "/");
		if (ms->exec_paths[i] == NULL)
			return (-1);
		free(tmp);
		i++;
	}
	return (0);
}

// splits path line by ':' and appends a backslash to paths
// returns -1 if allocation fails.
static int	ms_set_exec_paths(t_ms_data *ms, char *paths)
{
	paths = ft_strchr(paths, '/');
	ms->exec_paths = ft_split(paths, ':');
	if (ms->exec_paths == NULL)
		return (-1);
	if (ms_append_backslash_to_paths(ms) != 0)
	{
		ms_free_char2(ms->exec_paths);
		ms->exec_paths = NULL;
		return (-1);
	}
	return (0);
}

// scans list of env variables unless word PATH found.
// if not found, returns -1 and leaves ms->exec_paths = NULL.
// Else, ms->exec_paths is filled with the paths found in the environment.
// If the process failes, ms->exec_paths is set again to null and -1 
// is returned.

int	ms_get_exec_paths(t_ms_data *ms)
{
	t_ms_env_variable	*path;

	path = ms->env_vars_head;
	while (path != NULL)
	{
		if (ft_strnstr(path->env_variable, "PATH", 4) != NULL)
			break ;
		path = path->next;
	}
	if (path == NULL)
	{
		ms->exec_paths = NULL;
		return (-1);
	}
	else
	{
		if (ms_set_exec_paths(ms, path->env_variable) != 0)
		{
			ms->exec_paths = NULL;
			return (-1);
		}
	}
	return (0);
}
