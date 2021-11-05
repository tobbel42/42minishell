#include "../header/minishell.h"

void	ms_init_data(t_ms_data *ms)
{
	ms->line = NULL;
	ms->envars_head = NULL;
	ms->env_lines_count = 0;
	ms->exec_paths = NULL;
	ms->split_line = NULL;
	ms->task_list = NULL;
	ms->last_return = 0;
	ms->first_run_cd = 1;
	ms->home_dir = NULL;
	ms->is_pipe = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_ms_data	ms;

	if (argc > 1 || argv[1])
		return (-1);
	ms_init_data(&ms);
	if (ms_env_get(&ms, envp) != 0)
		return (-1);
	while (1)
	{
		ms_get_line(&ms);
		ms_get_exec_paths(&ms);
		ms_replace_args(&ms);
		ms_split(&ms);
		ms_create_task_list(&ms);
		if (!ms_iolinking_task_list(&ms))
			ms_lauch_task_list(&ms);
		ms_clean_task_list(&ms);
		if (ms.line && !ft_strncmp("exit", ms.line, 5))
		{
			write(1, "KTHXBYE\u2665\n", 11);
			break ;
		}
	}
	system("leaks minishell");
	return (0);
}
