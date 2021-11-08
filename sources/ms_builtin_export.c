#include "../header/minishell.h"

/*
	Checks standard conformity of given name.
*/
int	ms_env_valid_varname(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) == 1)
		return (0);
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) == 1 || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/*
	checks for correct input, if not it writes an error to the task.
	if name valid but no equal sign detected in definition: also error.
*/
static int	ms_error_check_new_var(t_ms_envar *new_var, t_ms_task *task, \
	char *envar_def)
{
	char	*tmps;

	if ((!new_var->name || !new_var->name[0]) || \
		(ms_env_valid_varname(new_var->name) != 1))
	{
		task->err_flag = 1;
		tmps = ft_strjoin("`", envar_def);
		task->err_msg = ft_strjoin(tmps, "': not a valid identifier");
		free(tmps);
		return (1);
	}
	if (ft_strnstr(envar_def, "=", ft_strlen(envar_def)) == NULL)
		return (1);
	return (0);
}

/*
	adds the variable passed, if found, to env, does nothing if not found.
*/
static int	ms_export_variable(t_ms_data *ms, char *envar_def, t_ms_task *task)
{
	t_ms_envar	*curr;
	t_ms_envar	*new_var;

	if (!envar_def)
		return (0);
	new_var = ms_env_newvar_def(envar_def);
	if (ms_error_check_new_var(new_var, task, envar_def) != 0)
	{
		ms_env_free_envar(new_var);
		return (1);
	}
	curr = ms->envars_head;
	while (curr->next->next != NULL)
	{
		if (ms_str_isequal(curr->next->name, new_var->name) == 1)
		{
			ms_env_repl_envar(curr, new_var);
			return (0);
		}
		curr = curr->next;
	}
	ms_env_add_after(curr, new_var);
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
	int	error;

	i = 1;
	error = 0;
	while (task->args[i])
	{
		if (ms_export_variable(ms, task->args[i], task) != 0)
			error = 1;
		i++;
	}
	return (error);
}
