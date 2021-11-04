#include "../header/minishell.h"

/*
//checks wheather the function is a buildin, returns 1 if yes, 0 if no
*/
int	ms_is_builtin(t_ms_task *task)
{
	if (!ft_strncmp(task->args[0], "echo", 5) || !ft_strncmp(task->args[0], "cd", 3)
		|| !ft_strncmp(task->args[0], "pwd", 4) || !ft_strncmp(task->args[0], "env", 4)
		|| !ft_strncmp(task->args[0], "export", 7) || !ft_strncmp(task->args[0], "unset", 6)
		|| !ft_strncmp(task->args[0], "env", 4) || !ft_strncmp(task->args[0], "exit", 5))
		return (1);
	return (0);
}

/*
//takes the name of the cmd, and tryes to find the absolut path,
//returns path, if found, or sets error_msg if not or no access rights
*/
char	*ms_get_path(t_ms_task *task, t_ms_data *ms_data)
{
	int		i;
	char	*test_path;

	if (task->err_flag)
		return (NULL);
	if (ms_is_builtin(task))
		return (NULL);
	if (!access(task->args[0], X_OK))
		return (ft_strdup(task->args[0]));
	i = 0;
	while (ms_data->exec_paths && ms_data->exec_paths[i] && errno == ENOENT)
	{
		test_path = ft_strjoin(ms_data->exec_paths[i], task->args[0]);
		if (!test_path)
			return (NULL); 
		if (!access(test_path, X_OK))
			return(test_path);
		free(test_path);
		i++;
	}
	task->err_flag = 1;
	task->err_msg = ft_strdup(strerror(errno));
	return (NULL);
}
