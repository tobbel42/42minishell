#include "../header/minishell.h"

/*
	frees all allocated nodes of the environmental variables' list
	as long as head != NULL (-> if list empty, does nothing.)
*/
void	ms_env_free_list(t_ms_data *ms)
{
	t_ms_envar	*current;
	t_ms_envar	*tmp;

	current = ms->envars_head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ms_env_free_envar(tmp);
		ms->env_lines_count--;
	}
}

/*
	Frees an environmental variable
*/
void	ms_env_free_envar(t_ms_envar *envar)
{
	if (envar->name != NULL)
		free(envar->name);
	if (envar->content != NULL)
		free(envar->content);
	free(envar);
}