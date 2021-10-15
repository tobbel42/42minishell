/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:56:42 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 17:52:26 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_valid_cmd_path(char *path)
{
	if (path == NULL)
		return (0);
	if (access(path, F_OK | X_OK) != -1)
	{
		return (1);
	}
	return (0);
}

int	add_command_to_list(t_cmds *cmds, char **args)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (-1);
	new_command->args = args;
	new_command->next = cmds->head;
	cmds->head = new_command;
	cmds->size++;
	return (0);
}

void	reverse_commands_list(t_cmds *cmds)
{
	t_cmds		reversed;
	t_command	*tmp;

	cmds_init(&reversed);
	while (cmds->head != NULL)
	{
		tmp = cmds->head;
		cmds->head = cmds->head->next;
		tmp->next = reversed.head;
		reversed.head = tmp;
		reversed.size++;
		cmds->size--;
	}
	cmds->head = reversed.head;
	cmds->size = reversed.size;
}

void	cmds_init(t_cmds *cmds)
{
	cmds->head = NULL;
	cmds->size = 0;
}

void	write_command_not_found(char *cmd_name)
{
	write(2, "command not found: ", 20);
	write(2, cmd_name, (sizeof(cmd_name) - 1));
	write(2, "\n", 1);
}
