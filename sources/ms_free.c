#include "../header/minishell.h"

// goes through dadatsructure and if entry not null frees entry
// if exitflag == 1, exits with status exitstatus
void	ms_free_and_exit(t_ms_data *ms, int exitflag, int exitstatus)
{
	ms_free_env_list(ms);
	ms_clean_task_list(ms);
	if (ms->line != NULL)
		free(ms->line);
	if (ms->exec_paths != NULL)
		ms_free_char2(ms->exec_paths);
	if (ms->split_line != NULL)
		ms_free_char2(ms->split_line);
	if (exitflag == 1)
		exit(exitstatus);
}

/*
// frees all allocated nodes of the environmental variables' list
// as long as head != NULL (-> if list empty, does nothing.)
*/
void	ms_free_env_list(t_ms_data *ms)
{
	t_ms_env_variable	*current;
	t_ms_env_variable	*tmp;

	current = ms->env_vars_head;
	while(current != NULL)
	{
		tmp = current;
		if (tmp->all != NULL)
			free(tmp->all);
		if (tmp->name != NULL)
			free(tmp->name);
		if (tmp->content != NULL)
			free(tmp->content);
		current = current->next;
		free(tmp);
		ms->env_lines_count--;
	}
}

/*
** Frees an array of pointers to string
*/
void	ms_free_char2(char **m)
{
	int	i;

	i = 0;
	while (m[i] != NULL)
	{
		free(m[i]);
		m[i] = NULL;
		i++;
	}
	if (m != NULL)
		free(m);
		
}