#include "../header/minishell.h"

/*
//opens the outfile in the either 0 -> truncate or 1 -> append mode
//if the file cant be opend, a blackhole-pipe is created
*/

void	ms_io_outfile(t_ms_task *task, int mode)
{
	int	fd;
	int	p[2];

	fd = 0;
	if (mode == 0)
		fd = open(task->args[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (mode == 1)
		fd = open(task->args[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
		pipe(p); // todo pipeprotect
		fd = p[1];
		close(p[0]);
	}
	if (task->prev)
		task->prev->fd_out = fd;
}