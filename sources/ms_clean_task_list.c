#include "../header/minishell.h"

/*
//frees a single task instance
*/
void	ms_free_task(t_ms_task *task)
{
	if (!task)
		return ;
	if (task->name)
		free(task->name);
	if (task->args)
		ms_free_char2(task->args);
	if (task->exec_path)
		free(task->exec_path);
	if (task->err_msg)
		free(task->err_msg);
	free(task);
}

/*
//frees the task_list of ms_data
*/
void	ms_clean_task_list(t_ms_data *ms_data)
{
	t_ms_task	*node;
	t_ms_task	*next_node;

	if (!ms_data->task_list)
		return ;
	node = ms_data->task_list;
	while (node)
	{
		next_node = node->next;
		ms_free_task(node);
		node = next_node;
	}
	ms_data->task_list = NULL;
}
