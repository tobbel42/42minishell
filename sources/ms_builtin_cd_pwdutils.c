#include "../header/minishell.h"

/*
	replaces the content of OLDPWD; if not unsetted before it
	builds OLDPWD instead at first usage of cd.
*/
void	ms_set_oldpwd(t_ms_data *ms, char *startwd)
{
	t_ms_envar	*curr;
	t_ms_envar	*oldpwd;

	curr = ms_get_envar(ms, "OLDPWD");
	if (curr != NULL)
	{
		ms_env_repl_content(curr, startwd);
		return ;
	}
	if (ms->first_run_cd == 1)
	{
		curr = ms->envars_head;
		while (curr->next)
			curr = curr->next;
		oldpwd = ms_env_newvar_nc("OLDPWD", startwd);
		curr->next = oldpwd;
		ms->env_lines_count++;
	}
}

/*
	replaces the content of PWD; if no PWD in env does nothing
*/
void	ms_set_pwd(t_ms_data *ms)
{
	t_ms_envar	*curr;
	char		*cwd;

	cwd = getcwd(NULL, MAXPATHLEN);
	if (cwd == NULL)
		return ;
	curr = ms_get_envar(ms, "PWD");
	if (curr != NULL)
	{
		ms_env_repl_content(curr, cwd);
		free(cwd);
		return ;
	}
	free(cwd);
}
