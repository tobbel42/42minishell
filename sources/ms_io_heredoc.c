#include "../header/minishell.h"

/*
//reads from stdin till del is entered
*/
static int	pipe_fill(char *del, int fd)
{
	char	*line;
	int		len;

	ms_rl_init();
	len = (int)ft_strlen(del);
	line = readline("> ");
	while (line && ft_strncmp(del, line, len))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	ms_rl_clean();
	close(fd);
	if (line)
		free(line);
	else
		return (1);
	return (0);
}

/*
//finds the coresponding cmd
*/
static t_ms_task	*heredoc_finder(t_ms_task *task)
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
//write smart comment here :)
*/
int	ms_io_heredoc(t_ms_task	*task)
{
	int			fd[2];
	t_ms_task	*target;

	if (pipe(fd))
	{
		ft_putendl_fd("minishell: internal error", 2);
		return (1);
	}	
	if (pipe_fill(task->args[1], fd[1]))
		return (1);
	target = heredoc_finder(task);
	if (target && target->err_flag != 2)
	{
		if (target->fd_in != 0)
			close(target->fd_in);
		target->fd_in = fd[0];
	}
	else
		close(fd[0]);
	return (0);
}
