#include "../header/minishell.h"

static t_ms_task	*outfile_finder(t_ms_task *task)
{
	t_ms_task	*node;

	node = task;
	while (node && node->next && ft_strncmp("|", node->next->name, 2))
	{
		if (ms_is_cmd(node->name))
			return (node);
		node = node->next;
	}
	while (node && ft_strncmp("|", node->name, 2))
	{
		if (ms_is_cmd(node->name))
			return (node);
		node = node->prev;
	}
	return (NULL);
}

/*
//opens the outfile in the either 0 -> truncate or 1 -> append mode
//if the file cant be opend, a blackhole-pipe is created
*/
int	ms_io_outfile(t_ms_task *task, int mode)
{
	int			fd;
	t_ms_task	*target;

	target = outfile_finder(task);
	if (target && target->err_flag != 2)
	{
		if (mode == 0)
			fd = open(task->args[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(task->args[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			task->err_flag = 1;
			task->err_msg = ft_strdup(strerror(errno));
			if (target)
				target->err_flag = 2;
		}
		else
		{
			if (target->fd_out != 1)
				close(target->fd_out);
			target->fd_out = fd;
		}
	}
	return (0);
}
