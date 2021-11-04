#include "../header/minishell.h"

/*
	goes through dadatsructure and if entry not null frees entry
	if exitflag == 1, exits with status exitstatus
*/
void	ms_free_and_exit(t_ms_data *ms, int exitflag, int exitstatus)
{
	ms_env_free_list(ms);
	ms_clean_task_list(ms);
	if (ms->line != NULL)
		free(ms->line);
	if (ms->exec_paths != NULL)
		ms_free_char2(ms->exec_paths);
	if (ms->split_line != NULL)
		ms_free_char2(ms->split_line);
	if (ms->home_dir != NULL)
		free(ms->home_dir);
	if (exitflag == 1)
		exit(exitstatus);
}

/*
	Frees an array of pointers to string
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
	m = NULL;
}
