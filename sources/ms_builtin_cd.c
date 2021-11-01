#include "../header/minishell.h"

/*
	If no path provided, do nothing.
	Changes current directory to given path if valid,else an error 
	is written to the task and -1 returned.
*/
int	ms_builtin_cd(t_ms_task *task)
{
	char	*tmp;

	if (!task->args[1])
		return (0);
	if (chdir(task->args[1]) == -1)
	{
		task->err_flag = 1;
		tmp = ft_strjoin(task->args[1], ": ");
		task->err_msg = ft_strjoin(tmp, strerror(errno));
		free(tmp);
		return (-1);
	}
	else
		return (0);
}
