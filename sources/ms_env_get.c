#include "../header/minishell.h"

/*
	itertates through envp and saves every substring as a node of the
	env. variable's linked list on its own.
	if error during allocation, frees already allocated elements and 
	returns -1
*/
int	ms_env_get(t_ms_data *ms, char **envp)
{
	int	i;

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
	return (0);
}

/*
	adds a node to the head of the list
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