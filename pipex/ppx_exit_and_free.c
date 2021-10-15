/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_exit_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:04:14 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 17:59:12 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	Free heap memory and exit the program if exitflag set to 1.
**	Following are functions that free specific targets, whereas this first
**	functionality aims to cover every allocated variable in the program.
*/
void	pipex_free_and_exit(t_pipex *ppx, t_cmds *cmds, int extflg, int status)
{
	if (ppx != NULL)
		free_pipex_data(ppx);
	if (cmds != NULL)
		free_commands_list(cmds);
	if (extflg == 1)
		pipex_exit(status);
}

void	free_pipex_data(t_pipex *ppx)
{
	if (ppx->exec_paths != NULL)
		ft_free_char2(ppx->exec_paths);
	if (ppx->infile_fd > 0)
		close(ppx->infile_fd);
	if (ppx->outfile_fd > 0)
		close(ppx->outfile_fd);
}

void	free_commands_list(t_cmds *cmds)
{
	t_command	*curr;

	curr = cmds->head;
	while (curr != NULL)
	{
		free_command(curr);
		curr = curr->next;
	}
}

void	free_command(t_command *cmd)
{
	ft_free_char2(cmd->args);
	free(cmd);
}

/*
**	Only exitpoint of the program.
**	Add here	system("leaks pipex");
*/
void	pipex_exit(int exitstatus)
{
	exit(exitstatus);
}
