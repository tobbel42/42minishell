#include "../header/minishell.h"

void	ms_io_heredoc(t_ms_task	*task)
{
	//toDo: launch as seperate process, different check for exit, safty
	char	*line;
	int		fd[2];
	int		len;

	if (pipe(fd))
	{
		return ;
	}
	len = (int)ft_strlen(task->args[1]);
	line = readline("> ");
	while (line && ft_strncmp(task->args[1], line, len))
	{
		ft_putendl_fd(line, fd[1]);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd[1]);
	t_ms_task *node = task;
	while (node && node->prev && ft_strncmp("|", node->prev->name, 2))
	{
		if (ms_is_cmd(node->name))
		{
			task->fd_in = fd[0];
			return ;
		}
		node = node->prev;
	}
	while (node && t_strncmp("|", node->name, 2))
	{
		if (ms_is_cmd(node->name))
		node = node->next;
	}
	
	
}