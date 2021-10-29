#include "../header/minishell.h"

/*
	adds the variable passed, if found, to env, does nothing if not found.
 */
static int	ms_export_variable(t_ms_data *ms, char *var_str)
{
	t_ms_env_variable	*new_var;
	t_ms_env_variable	*curr;
	t_ms_env_variable	*tmp;

	if (!var_str || ft_strnstr(var_str, "=", ft_strlen(var_str)) == NULL)
		return (0);
	new_var = ms_env_new_variable(var_str);
	curr = ms->env_vars_head;
	while (curr->next->next != NULL)
	{
		curr = curr->next;
	}
	tmp = curr->next;
	curr->next = new_var;
	new_var->next = tmp;
	return (0);
}

/* 
	iterates through the arguments of "export" and adds the 
	corresponding variable if found to env.
*/
int	ms_builtin_export(t_ms_data *ms, t_ms_task *task)
{
	int	i;

	i = 1;
	while (task->args[i])
	{
		ms_export_variable(ms, task->args[i]);
		i++;
	}
	return (0);
}
