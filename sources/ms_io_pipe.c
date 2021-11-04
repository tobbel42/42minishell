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

static void	pipe_to_in(t_ms_task *in_task, int fd)
{
	if (in_task)
	{
		if (in_task->fd_out != 1)
			close(in_task->fd_out);
		in_task->fd_out = fd;
	}
	else
		close(fd);
}

static void	pipe_to_out(t_ms_task *out_task, int fd)
{
	if (out_task)
	{
		if (out_task->fd_in != 0)
			close(out_task->fd_in);
		out_task->fd_in = fd;
	}
	else
		close(fd);
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
	pipe_to_in(in_task, fd[1]);
	pipe_to_out(out_task, fd[0]);
	return (0);
}
