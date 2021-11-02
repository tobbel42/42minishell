#include "../header/minishell.h"

/*
	adds the new variable into the linked list
*/
static void	ms_replace_variable(t_ms_envar *curr, \
	t_ms_envar *new_var)
{
	t_ms_envar	*tmpv;

	tmpv = curr->next;
	curr->next = new_var;
	new_var->next = tmpv->next;
	ms_env_free_envar(tmpv);
}

/*
	replaces the old version of the variable with the new one
*/
static void	ms_add_variable(t_ms_envar *curr, t_ms_envar *new_var)
{
	t_ms_envar	*tmpv;

	tmpv = curr->next;
	curr->next = new_var;
	new_var->next = tmpv;
}

/*
	checks for correct input, if not it writes an error to the task.
*/
static int	ms_error_check_new_var(t_ms_envar *new_var, t_ms_task *task, \
	char *var_str)
{
	char	*tmps;

	if (!new_var->name || !new_var->name[0])
	{
		task->err_flag = 1;
		tmps = ft_strjoin("`", var_str);
		task->err_msg = ft_strjoin(tmps, "': not a valid identifier\n");
		free(tmps);
		ms_env_free_envar(new_var);
		return (-1);
	}
	return (0);
}

/*
	adds the variable passed, if found, to env, does nothing if not found.
*/
static int	ms_export_variable(t_ms_data *ms, char *var_str, t_ms_task *task)
{
	t_ms_envar	*curr;
	t_ms_envar	*new_var;

	if (!var_str || ft_strnstr(var_str, "=", ft_strlen(var_str)) == NULL)
		return (0);
	new_var = ms_env_newvar_def(var_str);
	if (ms_error_check_new_var(new_var, task, var_str) != 0)
		return (-1);
	curr = ms->envars_head;
	while (curr->next->next != NULL)
	{
		if (mst_isequal_str(curr->next->name, new_var->name) == 1)
		{
			ms_replace_variable(curr, new_var);
			return (0);
		}
		curr = curr->next;
	}
	ms_add_variable(curr, new_var);
	ms->env_lines_count++;
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
		ms_export_variable(ms, task->args[i], task);
		i++;
	}
	return (0);
}
