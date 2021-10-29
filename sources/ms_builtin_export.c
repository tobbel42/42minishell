#include "../header/minishell.h"

/*
	adds the variable passed, if found, to env, does nothing if not found.
 */
static int	ms_export_variable(t_ms_data *ms, char *var_str, t_ms_task *task)
{
	t_ms_env_variable	*curr;
	t_ms_env_variable	*new_var;
	t_ms_env_variable	*tmp;
	int					exists;
	char				*tmps;

	if (!var_str || ft_strnstr(var_str, "=", ft_strlen(var_str)) == NULL)
		return (0);
	tmp = NULL;
	new_var = ms_env_new_variable(var_str);
	if (!new_var->name || !new_var->name[0])
	{
		task->err_flag = 1;
		tmps = ft_strjoin("`", var_str);
		task->err_msg = ft_strjoin(tmps, "': not a valid identifier\n");
		free(tmps);
		ms_free_env_var(new_var);
		return (-1);
	}
	exists = 0;
	curr = ms->env_vars_head;
	while (curr->next->next != NULL)
	{
		if (mst_isequal_str(curr->next->name, new_var->name) == 1)
		{
			exists = 1;
			break ;
		}
		curr = curr->next;
	}
	if (exists == 0)
	{
		tmp = curr->next;
		curr->next = new_var;
		new_var->next = tmp;
		ms->env_lines_count++;
		return (0);
	}
	else
	{
		tmps = curr->next->content;
		// printf("TO REPLACE: %s\n", tmps);
		curr->next->content = ft_strdup(new_var->content);
		free(tmps);
		ms_free_env_var(new_var);
		// printf("REPLACED: %s\n", curr->next->content);
		return (0);
	}
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
	// t_ms_env_variable *curr;
	// curr = ms->env_vars_head;
	// while (curr)
	// {
	// 	printf("all: %s, name: %s, content: %s\n",curr->all, curr->name, curr->content);
	// 	curr = curr->next;
	// }
	// ms_print_env_list(ms);
	return (0);
}
