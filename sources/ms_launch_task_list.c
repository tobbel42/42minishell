#include "../header/minishell.h"

/*
//relays incoming SIGQUIT(ctrl + |) and SIGINT(ctrl + c) to the child process
*/
void	sig_handler(int num)
{
	kill(g_pid, num);
	if (num == 3)
		write(1, "Quit: 3", 7);
	write(1, "\n", 1);
	rl_redisplay();
}

/*
//fork the process, and executes the command in the child
//the input and output filedescriptors of the child are set to the values of task
//the parent is initalising the signalrelaying to the child, and waits for it to exit
*/
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
		//printf("minishell: %s: %s\n", task->args[0], strerror(errno));
		exit(1);
	}
	else if (pid == -1)
		printf("minishell: fork_error: %s\n", strerror(errno));
	else
	{
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
		g_pid = pid;
		wait(&ms_data->last_return);
	}
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
	if (mst_isequal_str(task->args[0], "env") == 1)
		return (ms_builtin_env(ms, task));
	if (mst_isequal_str(task->args[0], "unset") == 1)
		return (ms_builtin_unset(ms, task));
	if (mst_isequal_str(task->args[0], "export") == 1)
		return (ms_builtin_export(ms, task));
	if (mst_isequal_str(task->args[0], "pwd") == 1)
		return (ms_builtin_pwd(task));
	if (mst_isequal_str(task->args[0], "cd") == 1)
		return (ms_builtin_cd(ms, task));
	if (mst_isequal_str(task->args[0], "echo") == 1)
		return (ms_builtin_echo(task));
	return (1);
}

/*
//iterates through the task-list, excuting all commands
//error messages are printed if needed
//any open pipes of a given task is closed after execution
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
			if (ms_execute_builtin(ms_data, node) == 1 && \
				ms_is_cmd(node->name) && node->exec_path)
				launch_cmd(node, ms_data);
				// printf("%s\n", node->name);
		}
		if (node->err_flag == 1) // I changed this from 'else if' to 'if' to print
		// errors from builtins, hope it does not create bugs for other stuff
		{
			if (ms_is_cmd(node->name))
			{
				printf("minishell: %s: %s\n", node->name, node->err_msg);
				ms_data->last_return = 127;
			}
			else if (ft_strncmp(node->name, "|", 2))
				printf("minishell: %s: %s\n", node->args[1], node->err_msg);
			else
				printf("minishell: pipe: %s\n", node->err_msg);
		}
		if (node->fd_in != 0)
			close(node->fd_in);
		if (node->fd_out != 1)
			close(node->fd_out);
		node = node->next;
	}
	return (1);
}
