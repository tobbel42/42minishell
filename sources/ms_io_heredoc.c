#include "../header/minishell.h"

void	ms_io_heredoc(t_ms_task	*task)
{
	//toDo: launch as seperate process, different check for exit, safty
	char	*line;
	int		fd[2];

	pipe(fd);
	int		len = (int)ft_strlen(task->args[1]);
	line = readline("> ");
	while (line && ft_strncmp(task->args[1], line, len))
	{
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
}