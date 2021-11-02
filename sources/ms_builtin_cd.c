#include "../header/minishell.h"

static void	ms_set_oldpwd(t_ms_data *ms, char *startwd)
{
	t_ms_envar	*curr;
	t_ms_envar	*oldpwd;

	curr = ms->envars_head;
	while(curr)
	{
		if (mst_isequal_str(curr->name, "OLDPWD") == 1)
		{
			ms_env_repl_content(curr, startwd);
			return ;
		}
		curr = curr->next;
	}
	if (ms->first_run_cd == 1)
	curr = ms->envars_head;
	while(curr->next)
		curr = curr->next;
	oldpwd = ms_env_newvar_nc("OLDPWD", startwd);
	curr->next = oldpwd;
}

static void	ms_set_pwd(t_ms_data *ms)
{
	t_ms_envar	*curr;
	char		*cwd;

	cwd = getcwd(NULL, MAXPATHLEN);
	curr = ms->envars_head;
	while (curr)
	{
		if (mst_isequal_str(curr->name, "PWD") == 1)
		{
			ms_env_repl_content(curr, cwd);
			free(cwd);
			return ;
		}
		curr = curr->next;
	}
	free(cwd);
}

// void	ms_cd_to_home(t_ms_task *task)
// {
// 	if (!task->args[1] || mst_isequal_string(task->args[1], "~") == 1)
// 	// find HOME and cd there
// 	curr = ms->envars_head;
// 	while(curr)
// 	{
// 		if (mst_isequal_str(curr->name, "HOME") == 1)
// 		{

// 			return ;
// 		}
// 		curr = curr->next;
// 	}
// 	if (mst_isequal_string(task->args[1], "-") == 1)
	// cd to oldpwd
	
// }

static char *ms_get_chdir_path(t_ms_data *ms, t_ms_task *task)
{
	t_ms_envar	*curr;

	curr = ms->envars_head;
	while (curr)
	{
		if (mst_isequal_str(curr->name, "HOME") == 1)
			break ;
		curr = curr->next;
	}
	if (!task->args[1])
	{
		if (curr)
			return (curr->content);
		else
		{
			task->err_flag = 1;
			task->err_msg = ft_strdup("HOME not set");
			return (NULL);
		}
	}
	if (mst_isequal_str(task->args[1], "~") == 1)
		return (ms->home_dir);
	if (mst_isequal_str(task->args[1], "-") == 1 || \
		mst_isequal_str(task->args[1], "-~") == 1)
	{
		curr = ms->envars_head;
		while (curr)
		{
			if (mst_isequal_str(curr->name, "OLDPWD") == 1)
			{
				if (mst_isequal_str(task->args[1], "-") == 1)
				{
					write(task->fd_out, curr->content, ft_strlen(curr->content));
					write(task->fd_out, "\n", 1);
				}
				return (curr->content);
			}
			curr = curr->next;
		}
		return (NULL);
	}
	return (task->args[1]);
}

/*
	If no path provided, do nothing.
	Changes current directory to given path if valid,else an error 
	is written to the task and -1 returned.
*/
int	ms_builtin_cd(t_ms_data *ms, t_ms_task *task)
{
	char		*startwd;
	char		*path;
	char		*tmp;

	startwd = getcwd(NULL, MAXPATHLEN);
	if (startwd == NULL)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
		return (-1);
	}
	path = ms_get_chdir_path(ms, task);
	if (!path)
	{
		free(startwd);
		return (-1);
	}
	if (chdir(path) == -1)
	{
		if (task->err_flag == 0)
		{
			task->err_flag = 1;
			tmp = ft_strjoin(task->args[1], ": ");
			task->err_msg = ft_strjoin(tmp, strerror(errno));
			free(tmp);
			free(startwd);
		}
		return (-1);
	}
	ms_set_oldpwd(ms, startwd);
	if (ms->first_run_cd == 1)
		ms->first_run_cd = 0;
	ms_set_pwd(ms);
	free(startwd);
	return (0);
}

