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

// /*
// 	If command is builtin, this function calls the corrresponding
// 	executing function, which returns 0 on success, -1 on failure.
// 	If not a builtin, 1 is returned.
// */
static void	ms_execute_builtin(t_ms_data *ms, t_ms_task *task, int mode)
{
	if (ms_str_isequal(task->args[0], "env") == 1)
		ms->last_return = ms_builtin_env(ms, task);
	if (ms_str_isequal(task->args[0], "unset") == 1)
		ms->last_return = ms_builtin_unset(ms, task);
	if (ms_str_isequal(task->args[0], "export") == 1)
		ms->last_return = ms_builtin_export(ms, task);
	if (ms_str_isequal(task->args[0], "pwd") == 1)
		ms->last_return = ms_builtin_pwd(task);
	if (ms_str_isequal(task->args[0], "cd") == 1)
		ms->last_return = ms_builtin_cd(ms, task);
	if (ms_str_isequal(task->args[0], "echo") == 1)
		ms->last_return = ms_builtin_echo(task);
	if (ms_str_isequal(task->name, "exit") == 1)
		ms->last_return = ms_builtin_exit(ms, task);
	if (mode == 1)
		exit(0);
}

/*
//sets the fd, then launches buildin or execve the cmd
*/
static void	child_routine(t_ms_task *task, t_ms_data *ms_data, char **env_array)
{
	int	fd_check[2];

	if (task->fd_in != 0)
		fd_check[0] = dup2(task->fd_in, 0);
	if (task->fd_out != 1)
		fd_check[1] = dup2(task->fd_out, 1);
	if (fd_check[0] != -1 && fd_check[1] != -1)
	{
		if (ms_is_builtin(task) != 1)
			execve(task->exec_path, task->args, env_array);
		else
			ms_execute_builtin(ms_data, task, 1);
	}
	exit(1);
}

/*
//forks nad launches the task, any signal is relayed to the child
//exit_status is set
*/
static int	launch_cmd(t_ms_task *task, t_ms_data *ms_data)
{
	int		pid;
	char	**env_array;

	env_array = ms_env_to_array(ms_data);
	pid = fork();
	if (pid == 0)
		child_routine(task, ms_data, env_array);
	else if (pid == -1)
		return (1);
	else
	{
		signal(SIGQUIT, sig_handler);
		signal(SIGINT, sig_handler);
		g_pid = pid;
		wait(&ms_data->last_return);
		ms_data->last_return /= 256;
	}
	if (env_array)
		ms_free_char2(env_array);
	return (0);
}

/*
//launches the task or prints its err_msg, closes all FDs beside the std
*/
int	ms_launch_task(t_ms_data *ms_data, t_ms_task *task)
{
	int	flag;

	flag = 0;
	if (!task->err_flag)
	{
		if (ms_is_builtin(task) == 1 && ms_data->is_pipe == 0)
		{
			ms_execute_builtin(ms_data, task, 0);
			ms_data->last_return = 0;
		}
		if ((ms_is_cmd(task->name) && task->exec_path)
			|| (ms_is_builtin(task) == 1 && ms_data->is_pipe == 1))
			flag = launch_cmd(task, ms_data);
	}
	if (task->err_flag == 1)
		ms_print_err_msg(ms_data, task);
	if (task->fd_in != 0)
		close(task->fd_in);
	if (task->fd_out != 1)
		close(task->fd_out);
	return (flag);
}
