#include "../header/minishell.h"

static void	launch_cmd(t_ms_task *task, t_ms_data *ms_data)
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
	If command is builtin, this function calls the corrresponding
	executing function, which returns 0 on success, -1 on failure.
	If not a builtin, 1 is returned.
*/
int	ms_execute_builtin(t_ms_data *ms, t_ms_task *task)
{
	int	i;

	i = 0;
	while (task->args[0][i])
	{
		task->args[0][i] = ft_tolower(task->args[0][i]);
		i++;
	}
	if (mst_isequal_str(task->args[0], "env") == 1)
		return (ms_builtin_env(ms, task));
	if (mst_isequal_str(task->args[0], "unset") == 1)
		return (ms_builtin_unset(ms, task));
	if (mst_isequal_str(task->args[0], "export") == 1)
		return (ms_builtin_export(ms, task));
	return (1);
}

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
			if (ms_execute_builtin(ms_data, node) == 1 && \
				ms_is_cmd(node->name) && node->exec_path)
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
