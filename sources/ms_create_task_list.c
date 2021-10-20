/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_task_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrossma <tgrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:58:16 by tgrossma          #+#    #+#             */
/*   Updated: 2021/10/20 18:11:58 by tgrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	is_cmd(char *line)
{
	if (!ft_strncmp("<", line, 2) || !ft_strncmp("<<", line, 3)
		|| !ft_strncmp(">", line, 2) || !ft_strncmp(">>", line, 3)
		|| !ft_strncmp("|", line, 2) || !ft_strncmp(";", line, 2))
		return (0);
	return (1);
}

static int	fill_args(t_ms_task *task, t_ms_data *ms_data, int *index)
{
	if (!ft_strncmp("|" , task->name, 2) || !ft_strncmp(";", task->name, 2))
	{
		task->args = (char **)malloc(sizeof(char *) * 2);
		if (!task->args)
			return (1);
		task->args[0] = ft_strdup(ms_data->split_line[*index]);
		task->args[1] = NULL;
		*index = *index + 1;
	}
	else if (!ft_strncmp("<", task->name, 2) || !ft_strncmp("<<", task->name, 3)
		|| !ft_strncmp(">", task->name, 2) || !ft_strncmp(">>", task->name, 3))
	{
		task->args = (char **)malloc(sizeof(char *) * 3);
		if (!task->args)
			return (1);
		task->args[0] = ft_strdup(ms_data->split_line[*index]);
		task->args[1] = ft_strdup(ms_data->split_line[*index + 1]);
		task->args[2] = NULL;
		*index = *index + 2;
	}
	else
	{
		int i = 0;
		int j = 0;
		while (ms_data->split_line[*index + i] && is_cmd(ms_data->split_line[*index + i]))
			i++;
		task->args = (char **)ft_calloc(sizeof(char *), i + 1);
		if (!task->args)
			return (1);
		while (j < i)
		{
			task->args[j] = ft_strdup(ms_data->split_line[*index + j]);
			j++;
		}
		*index = *index + i;
	}
	return (0);
}

t_ms_task	*ms_create_task(t_ms_data *ms_data, int *index)
{
	t_ms_task	*task;

	task = (t_ms_task *)malloc(sizeof(t_ms_task));
	if (!task)
		return (NULL);
	task->fd_in = 0;
	task->fd_out = 1;
	task->err_flag = 0;
	task->err_msg = NULL;
	// if (is_cmd(ms_data->split_line[*index]))
	// 	task->name = ms_data->split_line[*index];
	// else
	// 	task->name = ms_data->split_line[*index];
	task->name = ft_strdup(ms_data->split_line[*index]);
	task->err_flag = fill_args(task, ms_data, index);
	task->exec_path = NULL;
	return (task);
}

int	ms_create_task_list(t_ms_data *ms_data)
{
	int len;
	int index;

	index = 0;
	len = 0;
	while (ms_data->split_line[len])
		len++;
	ms_data->task_list = ms_create_task(ms_data, &index);
	t_ms_task *node = ms_data->task_list;
	while (index < len)
	{
		node->next = ms_create_task(ms_data, &index);
		node = node->next;
	}
	return (0);
}
