/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_task_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:07:00 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/27 13:09:22 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	launch_cmd(t_ms_task *task, t_ms_data *ms_data)
{
	int		pid;
	int		fd_check[2];
	char	**env_array;

	env_array = ms_env_to_array(ms_data);
	pid = fork();
	if (pid == 0)
	{
		if (task->fd_in != 0)
			fd_check[0] = dup2(task->fd_in, 0);
		if (task->fd_out != 1)
			fd_check[1] = dup2(task->fd_out, 1);
		if (fd_check[0] != -1 && fd_check[1] != -1)
			execve(task->exec_path, task->args, env_array);
		printf("minishell: %s: %s\n", task->args[0], strerror(errno));
		exit(1);
	}
	else if (pid == -1)
		printf("minishell: fork_error: %s\n", strerror(errno));
	else
		wait(&ms_data->last_return);
	if (env_array)
		ms_free_char2(env_array);
}


/*
//itterates over the task list, executing the commands or printing error messages
*/
int	ms_lauch_task_list(t_ms_data *ms_data)
{
	t_ms_task	*node;

	if (!ms_data && !ms_data->task_list)
		return (1);
	node = ms_data->task_list;
	while (node)
	{
		if (!node->err_flag)
		{
			if (ms_is_cmd(node->name) && node->exec_path)
				launch_cmd(node, ms_data);
		}
		else
		{
			printf("minishell: %s: %s\n", node->name, node->err_msg);
			ms_data->last_return = 127;
		}
		node = node->next;
	}
	return (1);
}
