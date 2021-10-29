#include "../header/minishell.h"

/*
	deletes the variable passed, if found, from env, does nothing if not found.
*/
int	ms_unset_variable(t_ms_data *ms, char *var_str)
{
	t_ms_env_variable	*curr;
	t_ms_env_variable	*tmp;
	int					found;

	if (!var_str)
		return (0);
	curr = ms->env_vars_head;
	found = 0;
	while (curr->next != NULL)
	{
		if (mst_isequal_str(var_str, curr->next->name) == 1)
		{
			found = 1;
			break ;
		}
		curr = curr->next;
	}
	if (found == 0)
		return (0);
	tmp = curr->next;
	curr->next = curr->next->next;
	ms_free_env_var(tmp);
	ms->env_lines_count--;
	return (0);
}

/*
	iterates through the arguments of "unset" and unsets the 
	corresponding variable if found in env.
*/
int	ms_builtin_unset(t_ms_data *ms, t_ms_task *task)
{
	int	i;

	i = 1;
	while (task->args[i])
	{
		ms_unset_variable(ms, task->args[i]);
		i++;
	}
	return (0);
}
