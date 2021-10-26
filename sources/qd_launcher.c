/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qd_launcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:16:12 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/26 16:49:20 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	qd_launch(t_ms_data *ms_data)
{
	t_ms_task	*node = NULL;
	int			pid;

	if (!ms_data->task_list)
		return (1);
	node = ms_data->task_list;
	while (node)
	{
		pid = fork();
		if (pid == 0)
			execve(node->exec_path, node->args, NULL);
		else
		{
			wait(NULL);
			printf("\nexecuted: %s\n", node->args[0]);
		}
		node = node->next;
	}
	return (1);
}