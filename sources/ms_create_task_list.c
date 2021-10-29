#include "../header/minishell.h"

/*
//used to analyse the type of task, returns 1 for commands
//and 0 for special tasks (<< , < , >> , > , |)
*/
int	ms_is_cmd(char *line)
{
	if (!ft_strncmp("<", line, 2) || !ft_strncmp("<<", line, 3)
		|| !ft_strncmp(">", line, 2) || !ft_strncmp(">>", line, 3)
		|| (!ft_strncmp("|", line, 2)))
		return (0);
	return (1);
}

/*
//counts the number of argument a given task takes, 
//for commands any number of argument is possible,
//special tasks take a fixed amount of arguments 
*/
static int	get_arg_count(t_ms_task *task, t_ms_data *ms_data, int *index)
{
	int	i;

	i = 1;
	if (ms_is_cmd(task->name))
	{
		while (ms_data->split_line[*index + i]
			&& ms_is_cmd(ms_data->split_line[*index + i]))
			i++;
	}
	else if (ft_strncmp(task->name, "|", 2))
		i = 2;
	return (i);
}

/*
//copy the number of argments form ms_data->split_string to task->args
*/
static int	fill_args(t_ms_task *task, t_ms_data *ms_data, int *index)
{
	int	i;
	int	j;

	if (task->err_flag)
		return (1);
	j = 0;
	i = get_arg_count(task, ms_data, index);
	task->args = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!task->args)
		return (1);
	while (ms_data->split_line[*index + j] && j < i)
	{
		task->args[j] = ms_clean_input(ms_data->split_line[*index + j], j);
		if (!task->args[j])
		{
			mst_free_char2(task->args);
			task->args = NULL;
			return (1);
		}
		j++;
	}
	*index = *index + i;
	return (0);
}

/*
//ToDo: discriminate between malloc errors-> clean up everything -> to user ?
//		and fail-to-find / incorrect access rights errors  
*/
static	t_ms_task	*ms_create_task(t_ms_data *ms_data,
									t_ms_task *prev, int *index)
{
	t_ms_task	*task;

	task = (t_ms_task *)ft_calloc(1, sizeof(t_ms_task));
	if (!task)
		return (NULL);
	task->prev = prev;
	task->next = NULL;
	task->fd_in = 0;
	task->fd_out = 1;
	task->name = ft_strdup(ms_data->split_line[*index]);
	task->args = NULL;
	task->exec_path = NULL;
	task->err_msg = NULL;
	if (!task->name)
		task->err_flag = 1;
	task->err_flag = fill_args(task, ms_data, index);
	if (task->err_flag)
	{
		ms_free_task(task);
		return (NULL);
	}
	if (ms_is_cmd(task->name) == 1)
		task->exec_path = ms_get_path(task, ms_data);
	return (task);
}

/*
//takes the split_line and groups the arguments in a double linked list,
//where every group is one element(task)
*/
int	ms_create_task_list(t_ms_data *ms_data)
{
	int			len;
	int			index;
	t_ms_task	*node;

	if (ms_data->task_list)
		ms_clean_task_list(ms_data);
	index = 0;
	len = 0;
	while (ms_data->split_line[len])
		len++;
	ms_data->task_list = ms_create_task(ms_data, NULL, &index);
	node = ms_data->task_list;
	while (index < len && node)
	{
		node->next = ms_create_task(ms_data, node, &index);
		if (!node->next)
		{
			ms_clean_task_list(ms_data);
			return (1);
		}
		node = node->next;
	}
	return (0);
}
