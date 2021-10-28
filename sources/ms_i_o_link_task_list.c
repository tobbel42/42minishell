/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_i_o_link_task_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:18:40 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/27 15:56:29 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// void	ms_iolink_infile(t_ms_data *ms, t_ms_task *task)
// {
// 	if(mst_isequal_str(task->args[0], "<") != 1 || !task->args[1] || task->args[2])
// 		return ;
// 	// task->fd_in
// }

void	ms_redirect_task_type(t_ms_data *ms)
{
	t_ms_task	*curr;

	curr = ms->task_list;
	while (curr != NULL)
	{
		// if (curr->name && curr->name[0])
		// {
		// 	if (mst_isequal_str(curr->name, "<<") == 1)
		// 		//  todo
		// 	if (mst_isequal_str(curr->name, ">>") == 1)
		// 		// todo
			// if (mst_isequal_str(curr->name, "<") == 1)
			// 	ms_iolink_infile(ms, curr);
		// 	if (mst_isequal_str(curr->name, ">") == 1)
		// 		// todo
		// 	if (mst_isequal_str(curr->name, "|") == 1)
		// 		// todo
		// }
		// if (ms_is_buildin(ms, curr->args[0]) == 1)
		curr = curr->next;
	}
}

int	ms_is_buildin(t_ms_data *ms, char *cmd)
{
	int i;

	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	if ((mst_isequal_str(cmd, "export") == 1) \
		|| (mst_isequal_str(cmd, "unset") == 1) \
		|| (mst_isequal_str(cmd, "env") == 1) \
		|| (mst_isequal_str(cmd, "cd") == 1) \
		||(mst_isequal_str(cmd, "pwd") == 1))
		return (1);
	return (0);
}


