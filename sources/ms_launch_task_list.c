#include "../header/minishell.h"

void	ms_print_err_msg(t_ms_data *ms_data, t_ms_task *task)
{
	if (ms_is_cmd(task->name))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(task->name, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(task->err_msg, 2);
		if (ms_is_builtin(task) != 1)
			ms_data->last_return = 127;
	}
	else if (ft_strncmp(task->name, "|", 2))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(task->args[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(task->err_msg, 2);
	}
	else
	{
		ft_putstr_fd("minishell: pipe: ", 2);
		ft_putendl_fd(task->err_msg, 2);
	}
}

/*
//iterates through the task-list, excuting all commands
//error messages are printed if needed
//any open pipes of a given task is closed after execution
*/
int	ms_lauch_task_list(t_ms_data *ms_data)
{
	t_ms_task	*node;
	int			flag;

	if (!ms_data && !ms_data->task_list)
		return (1);
	node = ms_data->task_list;
	flag = 0;
	while (node && !flag)
	{
		flag = ms_launch_task(ms_data, node);
		node = node->next;
	}
	if (flag)
	{
		ft_putstr_fd("minishell: fork_error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}
