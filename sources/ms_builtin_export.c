#include "../header/minishell.h"

static void	ms_add_variable_after(char *var_str, t_ms_env_variable *curr)
{
	t_ms_env_variable	*new_var;
	t_ms_env_variable	*tmp;

	new_var = ms_env_new_variable(var_str);
	tmp = curr->next;
	curr->next = new_var;
	new_var->next = tmp;
}

static void	ms_replace_content(char *var_str, t_ms_env_variable *curr)
{
	int		i;
	int		empty_content;
	int		strlen;
	char	*tmp;

	i = 0;
	empty_content = 1;
	while (var_str[i] != '\0')
	{
		if (var_str[i] == '=')
		{
			empty_content = 0;
			break ;
		}
		i++;
	}
	strlen = ft_strlen(var_str);
	tmp = curr->content;
	if (empty_content == 0)
		curr->content = ft_substr(var_str, i + 1, strlen - i - 1);
	else
		curr->content = NULL;
	free(tmp);
	printf("curr->all: %s\n", curr->all);
	printf("curr->name: %s\n", curr->name);
	printf("curr->content: %s\n", curr->content);
	printf("passed: %s\n", var_str);
}

/*
	adds the variable passed, if found, to env, does nothing if not found.
 */
static int	ms_export_variable(t_ms_data *ms, char *var_str)
{
	t_ms_env_variable	*curr;
	int					exists;

	if (!var_str || ft_strnstr(var_str, "=", ft_strlen(var_str)) == NULL)
		return (0);
	exists = 0;
	curr = ms->env_vars_head;
	while (curr->next->next != NULL)
	{
		if (ft_strnstr(var_str, curr->next->name, ft_strlen(var_str)) != NULL)
		{
			exists = 1;
			break ;
		}
		curr = curr->next;
	}
	if (exists == 0)
	{
		ms_add_variable_after(var_str, curr);
		ms->env_lines_count++;
	}
	else
	{
		// ms_unset_variable(ms, var_str);
		// ms_add_variable_after(var_str, curr);
		ms_replace_content(var_str, curr->next);
		printf("curr->next->content: %s\n", curr->next->content);
		printf("curr->next->name: %s\n", curr->next->name);
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
		ms_export_variable(ms, task->args[i]);
		i++;
	}
	ms_print_env_list(ms);
	return (0);
}
