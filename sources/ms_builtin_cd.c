#include "../header/minishell.h"

void	ms_replace_var_content(t_ms_envar *var, char *repl)
{
	char	*tmp;

	tmp = var->content;
	var->content = ft_strdup(repl);
	free(tmp);
}

void	ms_update_pwd_var(t_ms_data *ms, char *name)
{
	t_ms_envar	*curr;
	t_ms_envar	*pwdv;
	char		*tmp;
	char		*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, MAXPATHLEN);
	curr = ms->envars_head;
	while(curr)
	{
		if (mst_isequal_str(curr->name, name) == 1)
		{
			ms_replace_var_content(curr, cwd);
			return ;
		}
		curr = curr->next;
	}
	curr = ms->envars_head;
	while(curr->next)
		curr = curr->next;
	name = ft_strjoin(name, "=");
	tmp = ft_strjoin(name, cwd);
	free(name);
	pwdv = ms_env_newvar_def(tmp);
	free(tmp);
	curr->next = pwdv;
}

// todo: set oldpwd to current before cd and pwd to new after in env
// add oldpwd is not there, and delete at first run of shell?

// may unstatic functions for replacement

// also, in export, iterate until or check what _ is

/*
	If no path provided, do nothing.
	Changes current directory to given path if valid,else an error 
	is written to the task and -1 returned.
*/
int	ms_builtin_cd(t_ms_data *ms, t_ms_task *task)
{
	char		*tmp;
	// static int	pwd;
	// static int 	oldpwd;

	if (!task->args[1])
		return (0);
	ms_update_pwd_var(ms, "OLDPWD");
	if (chdir(task->args[1]) == -1)
	{
		task->err_flag = 1;
		tmp = ft_strjoin(task->args[1], ": ");
		task->err_msg = ft_strjoin(tmp, strerror(errno));
		free(tmp);
		return (-1);
	}
	ms_update_pwd_var(ms, "PWD");
	return (0);
}
