/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_execute_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:01:03 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/11 17:55:23 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	Body of instructions for the child processes where the command gets
**	executed. The stdout gets redirected to the writing end of the pipe.
*/
static int	child_process(t_command *cmd, t_pipex *ppx, char **envp)
{
	close(ppx->fd[0]);
	if (dup2(ppx->fd[1], STDOUT_FILENO) == -1)
	{
		perror("Dup2 child middle: ");
		return (-1);
	}
	execve(cmd->args[0], cmd->args, envp);
	perror("Execution failed: ");
	close(ppx->fd[1]);
	return (-1);
}

/*
**	Body of instructions for the parent process: the stdin gets redirected
**	to the reading end of the pipe and a wait statement waits for the
**	previous command to be executed.
*/
static int	parent_process(t_pipex *ppx)
{
	int	status;

	waitpid(-1, &status, 0);
	close(ppx->fd[1]);
	if (dup2(ppx->fd[0], STDIN_FILENO) == -1)
	{
		perror("Dup2 parent: ");
		return (-1);
	}
	return (0);
}

/*
**	PIPEX EXECUTION - LAUNCHING A COMMAND
**	The function generates a pipe and a child process in which the command
**	passed as an argumen will be executed. If a failure arises in the
**	process, -1 is retured.
*/
static int	launch_process(t_command *cmd, t_pipex *ppx, char **envp)
{
	if (pipe(ppx->fd) == -1)
	{
		perror("Pipe: ");
		return (-1);
	}
	ppx->pid = fork();
	if (ppx->pid < 0)
	{
		perror("Fork: ");
		return (-1);
	}
	if (ppx->pid == 0)
	{
		if (child_process(cmd, ppx, envp) != 0)
			return (-1);
	}
	else
	{
		if (parent_process(ppx) != 0)
			return (-1);
	}
	return (0);
}

/*
**	LAST COMMAND
**	For the last command the output is redirected not to the pipe but to
**	the outfile, thus this case-specific function is called.
*/
static int	launch_last_process(t_command *cmd, t_pipex *ppx, char **envp)
{
	int	status;

	ppx->pid = fork();
	if (ppx->pid < 0)
	{
		perror("Fork: ");
		return (-1);
	}
	if (ppx->pid == 0)
	{
		if (dup2(ppx->outfile_fd, STDOUT_FILENO) == -1)
		{
			perror("Dup2 child outfile : ");
			return (-1);
		}
		close(ppx->outfile_fd);
		execve(cmd->args[0], cmd->args, envp);
		perror("Execution failed: ");
		return (-1);
	}
	else
		waitpid(-1, &status, 0);
	return (0);
}

/*
**	PIPEX EXECUTION
**	After parsing this function iterates through the commands' stack and
**	launches the execution of the commands.
*/
void	execute_commands(t_pipex *ppx, t_cmds *cmds, char **envp)
{
	t_command	*curr;

	curr = cmds->head;
	while (curr->next != NULL)
	{
		if (launch_process(curr, ppx, envp) != 0)
			pipex_free_and_exit(ppx, cmds, 1, EXIT_FAILURE);
		curr = curr->next;
	}
	launch_last_process(curr, ppx, envp);
	close(ppx->outfile_fd);
	pipex_free_and_exit(ppx, cmds, 1, EXIT_SUCCESS);
}
