#include "../header/minishell.h"

static int	ms_error_handeling_unset(t_ms_task *task, char *envar_def)
{
	char	*tmps;

	if (!envar_def)
		return (-1);
	if (ms_env_valid_varname(envar_def) != 1)
	{
		task->err_flag = 1;
		tmps = ft_strjoin("`", envar_def);
		task->err_msg = ft_strjoin(tmps, "': not a valid identifier");
		free(tmps);
		return (1);
	}
	return (0);
}

/*
	deletes the variable passed, if found, from env, does nothing if not found.
*/
static int	ms_unset_variable(t_ms_data *ms, char *envar_def)
{
	t_ms_envar	*curr;
	t_ms_envar	*tmp;
	int			found;

	curr = ms->envars_head;
	found = 0;
	while (curr->next != NULL)
	{
		if (ms_str_isequal(envar_def, curr->next->name) == 1)
		{
			found = 1;
			break ;
		}
		curr = curr->next;
	}
	if (found == 0)
		return (0);
	if (ms_str_isequal(curr->next->name, "OLDPWD") == 1)
		ms->first_run_cd = 0;
	tmp = curr->next;
	curr->next = curr->next->next;
	ms_env_free_envar(tmp);
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
	int	error;

	i = 1;
	error = 0;
	while (task->args[i])
	{
		if (ms_error_handeling_unset(task, task->args[i]) == 0)
			ms_unset_variable(ms, task->args[i]);
		else
			error = 1;
		if (ms_str_isequal(task->args[i], "PATH") == 1)
		{
			ms_free_char2(ms->exec_paths);
			ms->exec_paths = NULL;
		}
		i++;
	}
	return (error);
}
