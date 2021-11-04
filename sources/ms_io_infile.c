#include "../header/minishell.h"

static t_ms_task	*infile_finder(t_ms_task *task)
{
	t_ms_task	*node;

	node = task;
	while (node && node->prev && ft_strncmp("|", node->prev->name, 2))
	{
		if (ms_is_cmd(node->name))
			return (node);
		node = node->prev;
	}
	while (node && ft_strncmp("|", node->name, 2))
	{
		if (ms_is_cmd(node->name))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/*
//tries to open the infile, and passes the fd to the next cmd
*/
int	ms_io_infile(t_ms_task *task)
{
	int			fd;
	t_ms_task	*target;

	fd = open(task->args[1], O_RDONLY);
	target = infile_finder(task);
	if (fd == -1)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
		//maby, if multi file open error and no cmd just 1 err msg, now for each
		if (target)
			target->err_flag = 2;
	}
	else if (target)
	{
		if (target->fd_in != 0)
			close(target->fd_in);
		target->fd_in = fd;
	}
	return (0);
}
