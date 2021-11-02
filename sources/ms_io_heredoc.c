#include "../header/minishell.h"

void	ms_io_heredoc(t_ms_task	*task)
{
	//toDo: launch as seperate process, different check for exit, safty
	char	*line;
	int		fd[2];

	pipe(fd);
	task->next->fd_in = fd[0];
	ft_putchar_fd('>', 1);
	line = get_next_line(0);
	printf("%s\n", line);
	while (line && ft_strncmp(task->args[1], line, (int)ft_strlen(task->args[1]) + 1))
	{
		ft_putchar_fd('>', 1);
		ft_putstr_fd(line, fd[1]);
		if (line)
			free (line);
		line = get_next_line(0);
		printf("%s\n", line);
	}
	if (line)
		free(line);
	close(fd[1]);
}