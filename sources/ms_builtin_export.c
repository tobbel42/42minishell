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
*/
static int	ms_error_check_new_var(t_ms_envar *new_var, t_ms_task *task, \
	char *envar_def)
{
	char	*tmps;

	if (!new_var->name || !new_var->name[0])
	{
		task->err_flag = 1;
		tmps = ft_strjoin("`", envar_def);
		task->err_msg = ft_strjoin(tmps, "': not a valid identifier");
		free(tmps);
		return (-1);
	}
	if (ms_env_valid_varname(new_var->name) != 1)
	{
		task->err_flag = 1;
		tmps = ft_strjoin("`", envar_def);
		task->err_msg = ft_strjoin(tmps, "': not a valid identifier");
		free(tmps);
		return (-1);
	}
	return (0);
}

/*
	adds the variable passed, if found, to env, does nothing if not found.
*/
static void	ms_export_variable(t_ms_data *ms, char *envar_def, t_ms_task *task)
{
	t_ms_envar	*curr;
	t_ms_envar	*new_var;

	if (!envar_def || ft_strnstr(envar_def, "=", ft_strlen(envar_def)) == NULL)
		return ;
	new_var = ms_env_newvar_def(envar_def);
	if (ms_error_check_new_var(new_var, task, envar_def) != 0)
	{
		ms_env_free_envar(new_var);
		return ;
	}
	curr = ms->envars_head;
	while (curr->next->next != NULL)
	{
		if (mst_isequal_str(curr->next->name, new_var->name) == 1)
		{
			ms_env_repl_envar(curr, new_var);
			return ;
		}
		curr = curr->next;
	}
	ms_env_add_after(curr, new_var);
	ms->env_lines_count++;
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
