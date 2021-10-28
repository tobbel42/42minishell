/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_i_o_link_task_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akamlah <akamlah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:18:40 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/27 15:46:38 by akamlah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// void	ms_iolink_infile(t_ms_data *ms, t_ms_task *task)
// {
// 	if(mst_isequal_str(task->args[0], "<") != 1 || !task->args[1] || task->args[2])
// 		return ;
// 	// task->fd_in
// }

int	ms_execute_builtin(t_ms_data *ms, t_ms_task *task)
{
	int i;

	i = 0;
	while (task->args[0][i])
	{
		task->args[0][i] = ft_tolower(task->args[0][i]);
		i++;
	}
	// if (mst_isequal_str(task->args[0], "export") == 1)
	// 	ms_builtin_export(ms, task);
	// if (mst_isequal_str(task->args[0], "unset") == 1)
	// 	ms_buildin_unset(ms, task);
	if (mst_isequal_str(task->args[0], "env") == 1)
		return (ms_builtin_env(ms, task));
	// if (mst_isequal_str(task->args[0], "cd") == 1)
	
	// if(mst_isequal_str(task->args[0], "pwd") == 1)
	
	return (2);
}


void	ms_redirect_task_type(t_ms_data *ms)
{
	t_ms_task	*curr;

	curr = ms->task_list;
	while (curr != NULL)
	{
		if (ms_execute_builtin(ms, curr) == 2)
			continue ;
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
		curr = curr->next;
	}
}
