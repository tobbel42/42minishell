#include "../header/minishell.h"

/*
	replaces content of an envar. if failure, it is set to null
	(by ft_strdup)
*/
void	ms_env_repl_content(t_ms_envar *var, char *repl)
{
	char	*tmp;

	tmp = var->content;
	var->content = ft_strdup(repl);
	free(tmp);
}

/*
	replaces the old version of the variable with the new one
*/
void	ms_env_repl_envar(t_ms_envar *curr, t_ms_envar *new_var)
{
	t_ms_envar	*tmpv;

	tmpv = curr->next;
	curr->next = new_var;
	new_var->next = tmpv->next;
	ms_env_free_envar(tmpv);
}

/*
	inserts the new variable into the linked list between "curr"
	and curr->next. "curr->next" may also be a null pointer.
*/
void	ms_env_add_after(t_ms_envar *curr, t_ms_envar *new_var)
{
	t_ms_envar	*tmpv;

	if (curr == NULL)
		return ;
	tmpv = curr->next;
	curr->next = new_var;
	new_var->next = tmpv;
}
