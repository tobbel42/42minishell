#include "../header/minishell.h"

/*
	Prints the environment to STDOUT. If "env" was called with any arguments,
	an error is signalized, an error message passed to the task and -1
	is returned.
*/
int	ms_builtin_env(t_ms_data *ms, t_ms_task *task)
{
	if (task->args[1] != NULL)
	{
		task->err_flag = 1;
		task->err_msg = ft_strjoin(task->args[1], ": No such file or directory\n");
		return (-1);
	}
	ms_print_env_list(ms);
	return (0);
}
