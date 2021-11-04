#include "../header/minishell.h"

/*
	itertates through envp and saves every substring as a node of the
	env. variable's linked list on its own.
	if error during allocation, frees already allocated elements and 
	returns -1
*/
int	ms_env_get(t_ms_data *ms, char **envp)
{
	int			i;
	t_ms_envar	*curr;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ms_env_add(ms, envp[i]) != 0)
		{
			ms_env_free_list(ms);
			return (-1);
		}
		i++;
	}
	ms_env_reverse_list(ms);
	curr = ms->envars_head;
	while (curr)
	{
		if (ms_str_isequal(curr->name, "HOME") == 1)
		{
			ms->home_dir = ft_strdup(curr->content);
			break ;
		}
		curr = curr->next;
	}
	return (0);
}

/*
	creates a new envar and adds it to the head of the env list
*/
int	ms_env_add(t_ms_data *ms, char *envar_def)
{
	t_ms_envar	*new_env_variable;

	new_env_variable = ms_env_newvar_def(envar_def);
	new_env_variable->next = ms->envars_head;
	ms->envars_head = new_env_variable;
	ms->env_lines_count++;
	return (0);
}
