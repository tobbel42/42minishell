#include "../header/minishell.h"

void	ms_io_pipe(t_ms_task *task)
{
	int	fd[2];
	int	err;

	if (!task->prev || !task->next)
		return ;
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
}

// goes through tasks and sets the file descriptors according to the special
// characters
void	ms_iolinking_task_list(t_ms_data *ms)
{
	t_ms_task	*curr;

	curr = ms->task_list;
	while (curr != NULL)
	{
		if (mst_isequal_str(curr->name, "<") == 1)
			ms_io_infile(curr);
		if (mst_isequal_str(curr->name, "<<") == 1)
 			ms_io_heredoc(curr);
		if (mst_isequal_str(curr->name, ">>") == 1)
			ms_io_outfile(curr, 1);
		if (mst_isequal_str(curr->name, ">") == 1)
			ms_io_outfile(curr, 0);
		if (mst_isequal_str(curr->name, "|") == 1)
			ms_io_pipe(curr);
		curr = curr->next;
	}
}