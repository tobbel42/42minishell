#include "../header/minishell.h"

int	ms_io_pipe(t_ms_task *task)
{
	int	fd[2];
	int	err;

	if (!task->prev || !task->next)
		return (1);
	err = pipe(fd);
	if (!err)
	{
		task->prev->fd_out = fd[1];
		task->next->fd_in = fd[0];
	}
	else
	{
		task->prev->err_flag = 2;
		task->next->err_flag = 2;
		task->err_flag = 1;
		task->err_msg = ft_strdup(strerror(errno));
	}
	return (0);
}

// goes through tasks and sets the file descriptors according to the special
// characters
int	ms_iolinking_task_list(t_ms_data *ms)
{
	t_ms_task	*curr;
	int			flag;

	curr = ms->task_list;
	flag = 0;
	while (curr != NULL && flag == 0)
	{
		if (ms_str_isequal(curr->name, "<") == 1)
			flag = ms_io_infile(curr);
		if (ms_str_isequal(curr->name, "<<") == 1)
			flag = ms_io_heredoc(curr);
		if (ms_str_isequal(curr->name, ">>") == 1)
			flag = ms_io_outfile(curr, 1);
		if (ms_str_isequal(curr->name, ">") == 1)
			flag = ms_io_outfile(curr, 0);
		if (ms_str_isequal(curr->name, "|") == 1)
			flag = ms_io_pipe(curr);
		curr = curr->next;
	}
	return (flag);
}
