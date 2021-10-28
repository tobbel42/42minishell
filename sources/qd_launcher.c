#include "../header/minishell.h"

void	qd_launch(t_ms_data *ms_data)
{
	t_ms_task	*node = NULL;
	int			pid;

	if (!ms_data->task_list)
		return ;
	node = ms_data->task_list;
	int	i = 0;
	while (node)
	{
		printf("%i\n", i);
		i = i + 1;
		if (node->exec_path)
		{
			pid = fork();
			if (pid == 0)
				execve(node->exec_path, node->args, NULL);
			if (pid == 0)
				break ;
			printf("%i\n", pid);
			wait(NULL);
		}
		printf("\nexecuted: %s\n", node->args[0]);
		node = node->next;
	}
}