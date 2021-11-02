#include "../header/minishell.h"

/*
	writes the current working directory to fd_out set in task.
	If getcwd failes, the corresponding message is passed to the
	task and -1 is returned.
*/
int	ms_builtin_pwd(t_ms_task *task)
{
	char	*cwd;

	cwd = getcwd(NULL, MAXPATHLEN);
	if (cwd == NULL)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
		return (-1);
	}
	write(task->fd_out, cwd, ft_strlen(cwd));
	write(task->fd_out, "\n", 1);
	free(cwd);
	return (0);
}
