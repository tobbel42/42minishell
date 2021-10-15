/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_parse_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:44:11 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 18:03:19 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	Util that returns the command passsed if it wass already passed with its
**	path, or finds and returns the path if the command was valid.
**	Prints "command not found" to strerr if no path found and returns null.
*/
static char	*get_cmd_path(t_pipex *ppx, char *word)
{
	int		i;
	char	*path;

	i = 0;
	if (ppx->exec_paths == NULL)
	{
		write_command_not_found(word);
		free(word);
		return (0);
	}
	while (ppx->exec_paths[i] != NULL && ppx->exec_paths != NULL)
	{
		path = ft_strjoin(ppx->exec_paths[i], word);
		if (is_valid_cmd_path(path) == TRUE)
		{
			free(word);
			return (path);
		}
		i++;
		free(path);
		path = NULL;
	}
	write_command_not_found(word);
	free(word);
	return (NULL);
}

/*
**	Takes a string as argument and checks if the first word of it is a command.
**	If so, the function gets the command's path if not already given and 
**	adds the command to the commans's list, saving the other words in the
**	string as arguments of the command.
*/
static int	parse_command(t_pipex *ppx, t_cmds *cmds, char *argvi)
{
	char	*path;
	char	**args;
	char	*word;

	word = ft_get_first_word(argvi);
	if (is_valid_cmd_path(word) == TRUE)
		path = word;
	else
		path = get_cmd_path(ppx, word);
	if (path == NULL)
		return (0);
	else
	{
		args = ft_split(argvi, ' ');
		free(args[0]);
		args[0] = path;
		if (add_command_to_list(cmds, args) != 0)
		{
			ft_free_char2(args);
			return (-1);
		}
	}
	return (0);
}

/*
**	COMMANDS PARSER
**	iterates through mian arguments and saves passed commands in linked list
**	if valid.
**	Returns error if non valid command encountered, if no commands found and
**	if the process registered some allocation failure.
**	If ppx->exec_paths was NULL, 
*/
int	get_commands(t_pipex *ppx, t_cmds *cmds, char **argv, int argc)
{
	int	i;

	cmds_init(cmds);
	i = 2;
	while (i < argc - 1)
	{
		if (parse_command(ppx, cmds, argv[i]) != 0)
		{
			return (-1);
		}
		i++;
	}
	if (cmds->size == 0)
		return (-1);
	reverse_commands_list(cmds);
	return (0);
}
