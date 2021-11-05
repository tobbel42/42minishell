#include "../header/minishell.h"

static t_ms_task	*intask_finder(t_ms_task *task)
{
	t_ms_task	*node;

	node = task->prev;
	while (node && ft_strncmp("|", node->name, 2))
	{
		if (ms_is_cmd(node->name))
			return (node);
		node = node->prev;
	}
	return (NULL);
}

static t_ms_task	*outtask_finder(t_ms_task *task)
{
	t_ms_task	*node;

	node = task->next;
	while (node && ft_strncmp("|", node->name, 2))
	{
		if (ms_is_cmd(node->name))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/*
//lays a pipe ToDo: refactor, errhandling ?
*/
int	ms_io_pipe(t_ms_task *task)
{
	int			fd[2];
	t_ms_task	*in_task;
	t_ms_task	*out_task;

	if (pipe(fd) == -1)
	{
		ft_putendl_fd("minishell: internal error", 2);
		return (1);
	}
	in_task = intask_finder(task);
	out_task = outtask_finder(task);
	if ((!in_task && !task->prev) || (!out_task && !task->next))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (1);
	}
	if (in_task && in_task->fd_out == 1)
		in_task->fd_out = fd[1];
	else
		close(fd[1]);
	if (out_task && out_task->fd_in == 0)
		out_task->fd_in = fd[0];
	else
		close(fd[0]);
	return (0);
}
