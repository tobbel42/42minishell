#include "../header/minishell.h"

/*
//tries to open the infile, and passes the fd to the next cmd
//if the file cant be open whatsoever an empty pipe is passed to the nxt cmd
*/
void	ms_io_infile(t_ms_task *task)
{
	int	fd;

	fd = open(task->args[1], O_RDONLY);
	
	if (fd == -1)
	{
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
		if (task->next)
			task->next->err_flag = 2;
	}
	else if (task->next)
		task->next->fd_in = fd;
}
