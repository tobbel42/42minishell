#include "../header/minishell.h"

/*
// adds a node to the head of the list
*/
int	ms_env_add(t_ms_data *ms, char *env_variable)
{
	t_ms_env_variable	*new_env_variable;

	new_env_variable = ms_env_new_variable(env_variable);
	new_env_variable->next = ms->env_vars_head;
	ms->env_vars_head = new_env_variable;
	ms->env_lines_count++;
	return (0);
}

static void	ms_reverse_env_list(t_ms_data *ms)
{
	t_ms_env_variable	*tmp;
	t_ms_env_variable	*rev_list_head;
	int					rev_list_size;

	rev_list_head = NULL;
	rev_list_size = 0;
	while (ms->env_vars_head != NULL)
	{
		tmp = ms->env_vars_head;
		ms->env_vars_head = ms->env_vars_head->next;
		tmp->next = rev_list_head;
		rev_list_head = tmp;
		rev_list_size++;
		ms->env_lines_count--;
	// printf("ENV LINES: %d\n", ms->env_lines_count);
	}
	ms->env_vars_head = rev_list_head;
	ms->env_lines_count = rev_list_size;
	// printf("ENV LINES: %d\n", ms->env_lines_count);
}

/*
// itertates through envp and saves every substring as a node of the
// env. variable's linked list on its own.
// if error during allocation, frees already allocated elements and 
// returns -1
*/
int	ms_get_env(t_ms_data *ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ms_env_add(ms, envp[i]) != 0)
		{
			ms_free_env_list(ms);
			return (-1);
		}
		// TEST
		// printf("%s\n", ms->env_vars_head->all);
		i++;
	}
	ms_reverse_env_list(ms);

	t_ms_env_variable	*currenv;
	currenv = ms->env_vars_head;
	while (currenv != NULL)
	{
		// printf("CURR ALL: %s\n", currenv->all);
		currenv = currenv->next;
	}
	// printf("ENV LINES: %d\n", ms->env_lines_count);

	return (0);
}

