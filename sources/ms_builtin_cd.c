#include "../header/minishell.h"

/*
	specifically sets ed to change to for "cd -" and "cd -~".
*/
static char	*ms_cd_dash_wd(t_ms_data *ms, t_ms_task *task)
{
	t_ms_envar	*curr;

	curr = ms_get_envar(ms, "OLDPWD");
	if (curr != NULL)
	{
		if (ms_str_isequal(task->args[1], "-") == 1)
		{
			write(task->fd_out, curr->content, ft_strlen(curr->content));
			write(task->fd_out, "\n", 1);
		}
		return (curr->content);
	}
	return (NULL);
}

/*
	sets correct path for cd for the following:
	cd : to $HOME as in env
	cd ~ : to ~ (works also with 'unset HOME')
	cd - : to $OLDPWD. Prints wd it changed to.
	cd  -~ : to $OLDPWD, nothing printed.
	cd "path" : to given string if no error.
*/
static char	*ms_get_chdir_path(t_ms_data *ms, t_ms_task *task)
{
	t_ms_envar	*curr;

	curr = ms_get_envar(ms, "HOME");
	if (!task->args[1])
	{
		if (curr != NULL)
			return (curr->content);
		else
		{
			task->err_flag = 1;
			task->err_msg = ft_strdup("HOME not set");
			return (NULL);
		}
	}
	if (ms_str_isequal(task->args[1], "~") == 1)
		return (ms->home_dir);
	if (ms_str_isequal(task->args[1], "-") == 1 || \
		ms_str_isequal(task->args[1], "-~") == 1)
		return (ms_cd_dash_wd(ms, task));
	return (task->args[1]);
}

/*
	error manager for chdir() failure.
*/
static int	ms_cd_chdir_error(t_ms_task *task, char *startwd)
{
	char		*tmp;

	if (task->err_flag == 0)
	{
		task->err_flag = 1;
		tmp = ft_strjoin(task->args[1], ": ");
		task->err_msg = ft_strjoin(tmp, strerror(errno));
		free(tmp);
	}
	free(startwd);
	return (1);
}

/*
	MAIN CALLER for cd.
	If no path provided, do nothing.
	Changes current directory to given path if valid,else an error 
	is written to the task and -1 returned.
*/
int	ms_builtin_cd(t_ms_data *ms, t_ms_task *task)
{
	char		*startwd;
	char		*path;

	startwd = getcwd(NULL, MAXPATHLEN);
	if (startwd == NULL)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
		return (1);
	}
	path = ms_get_chdir_path(ms, task);
	if (!path)
	{
		free(startwd);
		return (1);
	}
	if (chdir(path) == -1)
		return (ms_cd_chdir_error(task, startwd));
	ms_set_oldpwd(ms, startwd);
	if (ms->first_run_cd == 1)
		ms->first_run_cd = 0;
	ms_set_pwd(ms);
	free(startwd);
	return (0);
}
