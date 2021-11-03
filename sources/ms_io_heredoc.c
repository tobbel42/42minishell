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

int	ms_io_heredoc(t_ms_task	*task)
{
	//toDo: launch as seperate process, different check for exit, safty
	int		fd[2];

	if (pipe(fd))
	{
		ft_putendl_fd("minishell: internal error\n", 2);
		return (1);
	}
	if (pipe_fill(task->args[1], fd[1]))
		return (1);
	t_ms_task *node = task;

	while (node && node->prev && ft_strncmp("|", node->prev->name, 2))
	{
		if (ms_is_cmd(node->name))
		{
			node->fd_in = fd[0];
			return (0);
		}
		node = node->prev;
	}
	while (node && ft_strncmp("|", node->name, 2))
	{
	 	if (ms_is_cmd(node->name))
		{
			node->fd_in = fd[0];
			return (0);
		}	
		node = node->next;
	}
	return (1);
}