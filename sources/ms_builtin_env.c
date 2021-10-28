#include "../header/minishell.h"

int	ms_builtin_env(t_ms_data *ms, t_ms_task *task)
{
	if (task->args[1] != NULL)
		return (-1);
	ms_print_env_list(ms);
	return (0);
}
