/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_i_o_link_task_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:18:40 by akamlah           #+#    #+#             */
/*   Updated: 2021/10/28 11:47:43 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_iolink_infile(t_ms_task *task)
{
	if(mst_isequal_str(task->args[0], "<") != 1 || !task->args[1] || task->args[2])
		return ;
	task->fd_in = open(task->args[1], O_RDONLY);
	if (task->fd_in < 0)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
	}
}

// goes through tasks and sets the file descriptors according to the special
// characters
void	ms_iolinking_task_list(t_ms_data *ms)
{
	t_ms_task	*curr;

	curr = ms->task_list;
	while (curr != NULL)
	{
		if (mst_isequal_str(curr->name, "<") == 1)
			ms_iolink_infile(curr);
		// if (curr->name && curr->name[0])
		// {
		// 	if (mst_isequal_str(curr->name, "<<") == 1)
		// 		//  todo
		// 	if (mst_isequal_str(curr->name, ">>") == 1)
		// 		// todo
		// 	if (mst_isequal_str(curr->name, ">") == 1)
		// 		// todo
		// 	if (mst_isequal_str(curr->name, "|") == 1)
		// 		// todo
		// }
		curr = curr->next;
	}
}
